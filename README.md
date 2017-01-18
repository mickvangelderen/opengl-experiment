My playground for as-close-to-native-while-still-being-fun OpenGL applications.

# build

```bash
mkdir build
cd build
cmake ..
cmake --build .
# Create symbolic link to assets folder by hand for now. FIXME: CMake
# should do this eventually. 
ln -s ../assets assets
```

# Linux dependencies

Possibly missing some.

```
sudo apt-get install mesa-common-dev libgl1-mesa-dev xorg-dev
```

# Open problems

 * add_subdirectory vs ExternalProject_add https://coderwall.com/p/y3zzbq
 * testing windows and mac builds
