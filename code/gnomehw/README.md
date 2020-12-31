# Gnome HW

Example of 

## Compiling steps

1. Create a build directory:

    ```
    $ mkdir build && cd build
    ```

2. Install dependencies (Poco -> OpenSSL -> zlib):

    ```
    $ conan install ..
    ```

3. Configure the CMake project (Using MSVC 16 in this example):

    ```
    $ cmake .. -G "Visual Studio 16 2019"
    ```

4. Build it:

    ```
    $ cmake --build . --config Release
    ```

5. Run the application:

    ```
    $ .\bin\md5.exe
    c3fcd3d76192e4007dfb496cca67e13b
    ```