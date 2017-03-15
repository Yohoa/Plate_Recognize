A=imread('A.jpg');
rgb1= imread('1.jpg');
rgb=double(rgb1);
hsv=rgb2hsv(rgb);
gray = rgb2gray(rgb1);%rgb2gray转换成灰度图
% figure,imshow(gray),title('原始黑白图像');
s=strel('disk',13);                     %strel函数
Bgray=imopen(gray,s);                  %图像开运算
% figure,imshow(Bgray);title('背景图像'); %输出背景图像
Egray=imsubtract(gray,Bgray);            %两幅图相减
% figure,imshow(Egray);title('增强黑白图像');%输出黑白图像
fmax1=double(max(max(Egray)));        %Egray的最大值并输出双精度型
fmin1=double(min(min(Egray)));         %Egray的最小值并输出双精度型
level=(fmax1-(fmax1-fmin1)/1.3)/255;     %获得最佳阈值
bw22=im2bw(Egray,level);               %转换图像为二进制图像
bw2=double(bw22);
%   figure,imshow(bw22);title('车牌二值化图像');
d=0;d_1=0;d_2=0;
chapai=cell(1,3);
zuizhong=cell(1,3);
for i=1:3
      if i~=1  & d (i-1)>0 & dd(i-1)==7
        break;
     end
    if i==1
        [chapai{1},d(1)]=colorpanjue(rgb,bw2);
    end
    if i==2
       [chapai{2},d(2)]=hsvpanjue(hsv,bw2); 
    end
    if i==3
        [chapai{3},d(3)]=graypanjue(bw2);
    end
    if d(i)>0
       A=jiaozheng(chapai{i});
       C=lineps(A);
       C=qunxiejiaozheng(C);
       [zuizhong{i},KK(i),dd(i)]=fenge(C);
       juli(i)=abs(dd(i)-7);
    else
        juli(i)=100;
    end
end
max_d=max(d);
if max_d>0
[juli_min,index]=min(juli);
final=zuizhong{index};
    if dd(index)-KK(index)==7
              figure;title('车牌分割后图像');
             for i=1:dd(index)-KK(index)
                        subplot(1,dd(index)-KK(index),i);imshow(final{i});
             end
             success=1;
    else
             success=0;
    end
else
     success=0;
end
