%Step1 获取图像   装入待处理彩色图像并显示原始图像
Scolor = imread('cb36.jpg');%imread函数读取图像文件

%将彩色图像转换为黑白并显示
Sgray = rgb2gray(Scolor);%rgb2gray转换成灰度图
figure,imshow(Scolor),title('原始彩色图像');%figure命令同时显示两幅图
figure,imshow(Sgray),title('原始黑白图像');


%Step2 图像预处理   对Sgray 原始黑白图像进行开操作得到图像背景
s=strel('disk',13);%strel函数
Bgray=imopen(Sgray,s);%打开sgray s图像
figure,imshow(Bgray);title('背景图像');%输出背景图像
%用原始图像与背景图像作减法，增强图像
Egray=imsubtract(Sgray,Bgray);%两幅图相减
figure,imshow(Egray);title('增强黑白图像');%输出黑白图像

%Step3 取得最佳阈值，将图像二值化
fmax1=double(max(max(Egray)));%egray的最大值并输出双精度型
fmin1=double(min(min(Egray)));%egray的最小值并输出双精度型
level=(fmax1-(fmax1-fmin1)/3)/255;%获得最佳阈值
bw22=im2bw(Egray,level);%转换图像为二进制图像
bw2=double(bw22);
figure,imshow(bw2);title('图像二值化');%得到二值图像


%Step4 对得到二值图像作开闭操作进行滤波
grd=edge(bw2,'canny')%用canny算子识别强度图像中的边界
figure,imshow(grd);title('图像边缘提取');%输出图像边缘
bg1=imclose(grd,strel('rectangle',[5,19]));%取矩形框的闭运算

figure,imshow(bg1);title('图像闭运算[5,19]');%输出闭运算的图像
bg3=imopen(bg1,strel('rectangle',[5,19]));%取矩形框的开运算
figure,imshow(bg3);title('图像开运算[5,19]');%输出开运算的图像
bg2=imopen(bg3,strel('rectangle',[19,1]));%取矩形框的开运算
figure,imshow(bg2);title('图像开运算[19,1]');%输出开运算的图像

