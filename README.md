# MATLAB Wrapper Example Project

This project serves as a lightweight example for demonstrating how to wrap C++ code in MATLAB using GTSAM.

## Dependencies

We recommend installing the [gtwrap](https://github.com/borglab/wrap) project.

Once the repo is cloned, you can install it via:

```sh
mkdir build && cd build
cmake ..
sudo make install
```

## Compiling

We follow the regular build procedure inside the `example_project` directory:

```sh
mkdir build && cd build
cmake ..
make -j8
sudo make install

sudo ldconfig  # ensures the shared object file generated is correctly loaded
```

If you have a custom install location, denoted by `<install-path>`, you need to update your `LD_LIBRARY_PATH` environment variable.

```sh
export LD_LIBRARY_PATH=<install-path>/gtsam:$LD_LIBRARY_PATH
```

## Usage

Now you can open MATLAB and add the `gtsam_toolbox` to the MATLAB path

```matlab
addpath('/usr/local/gtsam_toolbox')
```

At this point you are ready to run the example project. Simply run code like regular MATLAB, e.g.

```matlab
pe = example.PrintExample();
pe.sayHello();
pe.sayGoodbye();
```

### Issues

If you see the compiler issue

```
fatal error: wrap/matlab.h: No such file or directory
    1 | #include <wrap/matlab.h>
      |          ^~~~~~~~~~~~~~~
```

this means either the gtwrap project is not installed, or you are using the wrapper as provided within GTSAM. In this case, we recommend (re-)installing the gtwrap project as the easiest fix.
