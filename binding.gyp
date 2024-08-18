{
  "targets": [
    {
      "target_name": "eot2ttf",
      "sources": [ 
        "src/eot2ttf_wrapper.cpp"
      ],
      "include_dirs": [
        "<!(node -e \"require('nan')\")",
        "libeot/inc/libeot"
      ],
      "ldflags" : [
        "-L<(module_root_dir)/build/Release",
        "-leot",
        "-Wl,-rpath,<(module_root_dir)/build/Release"
      ],
      "cflags": [
        "-Wno-cast-function-type"
      ],
      "cflags_cc": [
        "-Wno-cast-function-type"
      ],
      "actions": [
        {
          "action_name": "build_libeot",
          "inputs": [],
          "outputs": ["./libeot/.libs/"],
          "action": [
            "sh", "-c",
            "cd ./libeot && autoreconf --install && ./configure && make"
          ],
          "condition": "OS=='mac' or OS=='linux'"
        },
        {
            "action_name": "copy_libeot",
            "inputs": [],
            "outputs": ["./build/Release/"],
            "action": [
                "sh", "-c",
                "cp ./libeot/.libs/* ./build/Release/"
            ],
        }
      ],
      "condition": "OS=='mac' or OS=='linux'"
    }
  ]
}
