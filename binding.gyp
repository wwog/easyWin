{
    "targets": [
        {
            "target_name": "nfile",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "xcode_settings": {"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                               "CLANG_CXX_LIBRARY": "libc++",
                               "MACOSX_DEPLOYMENT_TARGET": "10.7",
                               },
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1},
            },
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": ["./cppsrc/nfile.cc"],
            "include_dirs": [
                "<!(node -p \"require('node-addon-api').include_dir\")",
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        },
        {
            "target_name": "nwinuser",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "xcode_settings": {"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                               "CLANG_CXX_LIBRARY": "libc++",
                               "MACOSX_DEPLOYMENT_TARGET": "10.7",
                               },
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1},
            },
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": ["./cppsrc/nwinuser.cc"],
            "include_dirs": [
                "<!(node -p \"require('node-addon-api').include_dir\")",
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        },
        {
            "target_name": "ndraw",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "xcode_settings": {"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                               "CLANG_CXX_LIBRARY": "libc++",
                               "MACOSX_DEPLOYMENT_TARGET": "10.7",
                               },
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1},
            },
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": ["./cppsrc/ndraw.cc"],
            "include_dirs": [
                "<!(node -p \"require('node-addon-api').include_dir\")",
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        },
        {
            "target_name": "nprocess",
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "xcode_settings": {"GCC_ENABLE_CPP_EXCEPTIONS": "YES",
                               "CLANG_CXX_LIBRARY": "libc++",
                               "MACOSX_DEPLOYMENT_TARGET": "10.7",
                               },
            "msvs_settings": {
                "VCCLCompilerTool": {"ExceptionHandling": 1},
            },
            "cflags!": ["-fno-exceptions"],
            "cflags_cc!": ["-fno-exceptions"],
            "sources": ["./cppsrc/nprocess.cc"],
            "include_dirs": [
                "<!(node -p \"require('node-addon-api').include_dir\")",
                "<!@(node -p \"require('node-addon-api').include\")"
            ],
            'defines': ['NAPI_DISABLE_CPP_EXCEPTIONS'],
        }
    ]
}
