{
  "targets": [
    {
      "target_name": "nlibroboint",
      "cflags!": [
        "-fno-exceptions"
      ],
      "cflags_cc!": [
        "-fno-exceptions"
      ],
      "sources": [
        "./src/index.cpp",
        "./src/RoboInterface.cpp"
      ],
      "include_dirs": [
        "<!@(node -p \"require('node-addon-api').include\")"
      ],
      "link_settings": {
        "libraries": [
          "-lroboint"
        ]
      },
      "defines": [
        "NAPI_DISABLE_CPP_EXCEPTIONS"
      ]
    }
  ]
}