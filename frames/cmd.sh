/home/lgertrud/sgoinfre/ffmpeg-release-amd64-static/ffmpeg-7.0.2-amd64-static/ffmpeg -framerate 30 -i frame_%04d.ppm -c:v libx264 -crf 0 -preset veryslow -pix_fmt yuv444p video.mp4
