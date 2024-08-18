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
        "-L../libeot/.libs",
        "-leot.0"
   			"-Wl,-rpath,'$$ORIGIN'"
	    ],
      "copies": [
        {
          "destination": "<(module_root_dir)/build/Release",
          "files": ["libeot/.libs/libeot.0.dylib"]
        }
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
      ]
    }
  ]
}