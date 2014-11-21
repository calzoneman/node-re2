{
  "targets": [
    {
      "target_name": "re2",
      "sources": [
        "src/node_re2.cc"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")", "/usr/include"],
      "libraries": ["-lre2", "-lpthread"]
    }
  ]
}
