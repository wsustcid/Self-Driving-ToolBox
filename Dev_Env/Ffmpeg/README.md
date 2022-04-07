# FFMPGE

参考教程：https://zhuanlan.zhihu.com/p/67878761

## 1. Installation

```bash
# For Ubuntu 
sudo add-apt-repository ppa:jonathonf/ffmpeg-4
sudo apt-get update
sudo apt-get install ffmpeg

# Fow Win: https://www.wikihow.com/Install-FFmpeg-on-Windows
```



## 2. Quick Start

```python
## 视频剪辑
ffmpeg -ss 00:00:00 -t 00:00:30 -i test.mp4 -vcodec copy -acodec copy output.mp4 # -ss 指定从什么时间开始; -t 指定需要截取多长时间; -i 指定输入文件

## 视频转为GIF
ffmpeg -i small.mp4 small.gif # 将视频 MP4 转化为 GIF
ffmpeg -t 3 -ss 00:00:02 -i small.mp4 small-clip.gif #将视频中的一部分转换为GIF：从视频中第二秒开始，截取时长为3秒的片段转化为 gif
ffmpeg -i small.mp4 -b 2048k small.gif #转化高质量 GIF： 默认转化是中等质量模式，若要转化出高质量的 gif，可以修改比特率
ffmpeg -t 5 -ss 00:00:01 -i fc_10.mp4 -vf scale=640:-1 fc_10.gif # 指定输出大小

## 从视频提取图片 
ffmpeg -i 110.mp4 -r 10 -f image2 -ss 00:00:08 -t 22 110-%3d.png
#-r 帧速度 -f 输出格式 image-%2d.png 图像命名 -ss 截取帧初始时间 -vframes 截取多少帧 -t 取t秒时间的帧

## 图片转视频
ffmpeg -i rgb_%5d.jpg -r 25 -vcodec mpeg4 test.mp4
```



将 GIF 转化为 MP4
ffmpeg -f gif -i animation.gif animation.mp4
也可以将 gif 转为其他视频格式

ffmpeg -f gif -i animation.gif animation.mpeg
ffmpeg -f gif -i animation.gif animation.webm
加倍速播放视频
ffmpeg -i input.mov -filter:v "setpts=0.5*PTS" output.mov
定义帧率 16fps:

ffmpeg -i input.mov -r 16 -filter:v "setpts=0.125*PTS" -an output.mov
慢倍速播放视频
ffmpeg -i input.mov -filter:v "setpts=2.0*PTS" output.mov

作者：97690CE50CC872D
链接：https://www.jianshu.com/p/9af00bfe21b3
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

## 使用
# 合并视频
//截取从头开始的30s
ffmpeg -ss 00:00:00 -t 00:00:30 -i keyoutput.mp4 -vcodec copy -acodec copy split.mp4
//截取从30s开始的30s
ffmpeg -ss 00:00:30 -t 00:00:30 -i keyoutput.mp4 -vcodec copy -acodec copy split1.mp4
//进行视频的合并
ffmpeg -f concat -i list.txt -c copy concat.mp4
在list.txt文件中，对要合并的视频片段进行了描述。
内容如下


file ./split.mp4
file ./split1.mp4

作者：SHUTUP
链接：https://www.jianshu.com/p/eff314074177
来源：简书
著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。

ffmpeg -i input.mp4 -vf scale=1280:-1 -c:v libx264 -preset veryslow -crf 24 output.mp4

Convert .move To .mp4

ffmpeg -i in.mov -vcodec copy -acodec aac -strict experimental -ab 128k out.mp4










jpg本来就是高度压缩的图像格式,要想继续压缩图片文件大小,只能是降低分辨率或者降低图片质量,保存的图片本来就分辨率过高,降低一半的分辨率会大大减少图片占用的空间

安装imagemagick

1
$ sudo apt-get install imagemagick
imagemagick的命令convert可以完成此任务,其参数-resize用来改变图片尺寸,可以直接指定像素值,也可以指定缩放百分比。而如果想降低图片的质量,可以用convert的-quality参数,质量值为0-100之间的数值,数字越大,质量越好,一般指定70-80,基本上看不出前后的差别。

用下面的命令批量修改图片分辨率为原来的1/4大小,同时保持原图片比例

1
$ find ./ -regex '.*\(jpg\|JPG\)' -exec convert -resize 50%x50% {} {} \;
用规则表达式把jpg和JPG后缀图片一网打尽,{}代表查找到的文件,这里没有改变convert前后的文件名,最后是转义的分号表示一个迭代的处理完成。
也可以用以下命令

1
$ find ./ -name '*jpg' -o -name '*JPG' -exec convert -resize 50%x50% {} {} \;

## 3. Advanced Tutorial

