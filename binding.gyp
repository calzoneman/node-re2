{
  "targets": [
    {
      "target_name": "addon",
      "sources": [
        "addon.cc"
      ],
      "include_dirs": ["<!(node -e \"require('nan')\")", "/usr/include"],
      "libraries": ["-lre2", "-lpthread"]
    }
  ]
}
