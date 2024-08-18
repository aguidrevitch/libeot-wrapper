#include <nan.h>
#include "libeot.h"
#include <iostream>
#include <fstream>
#include <dlfcn.h>

#if defined(_WIN32) || defined(_WIN64)
    #include <windows.h>
    #define LIBRARY_NAME "libeot.0.dll"
#elif defined(__APPLE__) || defined(__MACH__)
    #include <dlfcn.h>
    #define LIBRARY_NAME "./libeot/.libs/libeot.0.dylib"
#else
    #include <dlfcn.h>
    #define LIBRARY_NAME "./libeot/.libs/libeot.0.so"
#endif

using namespace v8;

void *handle;  // Handle to the dynamically loaded library

// Helper function to convert a JavaScript Buffer to a C++ uint8_t array
uint8_t* BufferToUint8Array(Local<Object> bufferObj, unsigned int &size) {
    size = node::Buffer::Length(bufferObj);
    uint8_t* bufferData = (uint8_t*) malloc(size);
    memcpy(bufferData, node::Buffer::Data(bufferObj), size);
    return bufferData;
}

// Wrapper for the EOT2ttf_file function
NAN_METHOD(EOT2ttfFile) {
    // Load the EOT2ttf_file function from the shared library
    typedef EOTError (*EOT2ttfFileFunc)(const uint8_t *, unsigned, EOTMetadata *, FILE *);
    EOT2ttfFileFunc EOT2ttf_file = (EOT2ttfFileFunc)dlsym(handle, "EOT2ttf_file");
    
    const char* dlsym_error = dlerror();
    if (dlsym_error) {
        Nan::ThrowError("Cannot load symbol 'EOT2ttf_file'");
        return;
    }

    if (info.Length() != 3) {
        Nan::ThrowTypeError("Wrong number of arguments");
        return;
    }

    // Argument 0: font (Buffer)
    if (!info[0]->IsObject() || !node::Buffer::HasInstance(info[0])) {
        Nan::ThrowTypeError("Argument 0 must be a Buffer");
        return;
    }
    unsigned int fontSize;
    uint8_t* font = BufferToUint8Array(info[0].As<Object>(), fontSize);

    // Argument 1: metadataOut (object)
    if (!info[1]->IsObject()) {
        Nan::ThrowTypeError("Argument 1 must be an object");
        return;
    }
    EOTMetadata metadataOut = {}; // Assuming EOTMetadata has a default constructor or zero-initialization

    // Argument 2: out (string - file path)
    if (!info[2]->IsString()) {
        Nan::ThrowTypeError("Argument 2 must be a string (file path)");
        return;
    }
    Nan::Utf8String utf8Value(info[2]);
    std::string filePath(*utf8Value);

    FILE *outFile = fopen(filePath.c_str(), "wb");
    if (outFile == NULL) {
        Nan::ThrowError("Could not open the output file");
        free(font);
        return;
    }

    // Call the EOT2ttf_file function
    EOTError result = EOT2ttf_file(font, fontSize, &metadataOut, outFile);

    fclose(outFile);
    free(font);

    // Return the EOTError enum as the result
    info.GetReturnValue().Set(Nan::New(result));
}


// Module initialization function
NAN_MODULE_INIT(Init) {
    // see below for the CLEANUP function
    // node::AtExit(CLEANUP);
    
    // Load the shared library
    handle = dlopen(LIBRARY_NAME, RTLD_LAZY);
    if (!handle) {
        std::string errorMsg = "Cannot open " + std::string(LIBRARY_NAME);
        Nan::ThrowError(errorMsg.c_str());
        // Nan::ThrowError("Cannot open " + std::string(LIBRARY_NAME)).c_str());
        return;
    }

    // Export the EOT2ttfFile function to JavaScript
    Nan::Set(target, Nan::New("EOT2ttfFile").ToLocalChecked(),
        Nan::GetFunction(Nan::New<FunctionTemplate>(EOT2ttfFile)).ToLocalChecked());
    
}

// Module cleanup function (called when the module is unloaded)
void CLEANUP(void* arg) {
    if (handle) {
        dlclose(handle);
    }
}

NODE_MODULE(eot2ttf, Init)
