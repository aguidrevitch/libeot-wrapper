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
        "-L<(module_root_dir)/build/Release/",
        "-leot",
        "-Wl,-rpath,'$$ORIGIN'"
      ],
      "cflags": [
        "-Wno-cast-function-type"
      ],
      "cflags_cc": [
        "-Wno-cast-function-type"
      ],
      "copies": [
        {
          "destination": "<(module_root_dir)/build/Release",
          "files": [
            "<!@(ls -1 libeot/.libs/*)",
          ],
        },
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
        }
      ],
      "condition": "OS=='mac' or OS=='linux'"
    }
  ]
}
