<p align="center">
  <img src="https://github.com/Happykat/R.O.C-SERVER/blob/development/assets/logo-roc-flat.png"/>
</p>

# R.O.C-SERVER

R.O.C-SERVER is a video server able to stream h.264 encoded video from several cameras to

several clients. It automatically synchronise the cameras together. The configuration is 
easy with one simple configuration file.

It is heavily dependent of OpenCV , so that a lot of image processing are possible on the
stream(s) in live. like face detection , canny , eye detection etc...

You can control it with the built in interpretor and / or by a TCP connection.

## Installation

Install all the dependencies before building R.O.C-SERVER

- CUDA
- V4l / V4l2
- protobuf 3.X
- ffmpeg (swscale - avformat)
- x264
- opencv 3.X

Then create a directory for the build :

``` mkdir build

cd into this directory :

``` cd build

start cmake

``` cmake ..

If everything went good , you can now run make :

``` make

## Usage

simply start the server : ./ROC
if you encouter any error , please make sure that your configuration file is correct.

The server has to be currently started from the directory containing the config folder
Some known problems :

- Adress Already in use : Tcp or RTSP server adress already in use , just wait a few minutes and try again
- Index V4l2 X incorrect : The camera driver might have crashed , try reseting the cameras (check /dev/videoX)

## Contributing

1. Fork it!
2. Create your feature branch: `git checkout -b my-new-feature`
3. Commit your changes: `git commit -am 'Add some feature'`
4. Push to the branch: `git push origin my-new-feature`
5. Submit a pull request :D


## License

This project is Open Source , feel free to use it and redistribute it as you want.
