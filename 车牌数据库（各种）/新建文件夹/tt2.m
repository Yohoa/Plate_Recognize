%对定位车牌预处理：去除边框和铆钉 
clear all;clc; 
f=imread('A.jpg');%读入定位后的车牌 
% figure(1),imshow(f); 
%threshold=graythresh(f);%二值化阈值 
f1=im2bw(f,0.75);%二值化 
 figure(2),imshow(f1);%显示二值化车牌图像 
[x,y]=size(f1); 
m=zeros(x,1); 
for i=1:x 
    for j=1:y 
        if(f1(i,j)==1)          
            m(i,1)=m(i,1)+1;%行扫描统计每行白色像素点个数 
        end 
    end 
end 
k=round(x/4); 
for i=1:k 
    if m(i,1)>round(y*0.15)&&m(i,1)<round(y*0.8) 
        k=k-1; 
    end 
end 
for i=1:k 
    for j=1:y 
        if (f1(i,j)==1) 
            f1(i,j)=0;%去除上边框和上边的铆钉 
        end 
    end 
end 
k=round(x/4); 
for i=1:k 
    if m(x-i,1)>round(y*0.15)&&m(x-i,1)<round(y*0.8) 
        k=k-1; 
    end 
end 
for i=x-k:x 
    for j=1:y 
        if (f1(i,j)==1) 
            f1(i,j)=0;%去除车牌下边框 
        end 
    end 
end 
figure(3),imshow(f1);%显示去除上下边框后的车牌 
n=zeros(1,y); 
for j=1:y 
    for i=1:x 
        if f1(i,j)==1 
           n(1,y)=n(1,y)+1;%列扫描统计每列白色像素点个数 
        end 
    end 
end 
for j=1:y/25 
    for i=1:x 
        if f1(i,j)==1 
           f1(i,j)=0;%去除车牌左边框 
        end 
    end 
end 
% figure(4),imshow(f1);%显示去除左边框后的车牌 
for j=round(y-y/25):y 
    for i=1:x 
        if f1(i,j)==1 
           f1(i,j)=0;%去除车牌右边框 
        end 
    end 
end 
figure(5),imshow(f1);%显示去除右边框后的车牌 
%字符分割程序 
p=zeros(1,y); 
for j=1:y 
    for i=1:x 
        if f1(i,j)==1 
           p(1,j)=p(1,j)+1;%列扫描统计每列白色像素点个数 
        end 
    end 
end 
py1=1; 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
p1=py1; 
while (p(1,py1)>=1)&&(py1<round(y/6)) 
    py1=py1+1; 
end 
if (py1-py2)<round(y*0.05) 
    py2=py1; 
    while(p(1,py1)<=2) 
        py1=py1+1; 
    end 
end 
while (p(1,py1)>=1)&&(py1<round(y/6))||(py1-py2)<round(y*0.05) 
    py1=py1+1; 
end 
diyi=f1(:,py2:py1); 
figure(6),imshow(diyi);%显示第一个字符 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y/3.5)) 
    py1=py1+1; 
end 
dier=f1(:,py2:py1); 
figure(7),imshow(dier);%显示第二个字符 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y/2)) 
    py1=py1+1; 
end 
disan=f1(:,py2:py1); 
figure(8),imshow(disan);%显示第三个字符 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y/1.5)) 
    py1=py1+1; 
end 
disi=f1(:,py2:py1); 
figure(9),imshow(disi);%显示第四个字符 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y)) 
    py1=py1+1; 
end 
diwu=f1(:,py2:py1); 
figure(10),imshow(diwu);%显示第五个字符 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y)) 
    py1=py1+1; 
end 
diliu=f1(:,py2:py1); 
figure(11),imshow(diliu);%显示第六个字符 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y)) 
    py1=py1+1; 
end 
diqi=f1(:,py2:py1); 
figure(12),imshow(diqi);%显示第七个字符 
w.a=diyi;imwrite(w.a,'w_a.bmp'); 
w.b=dier;imwrite(w.b,'w_b.bmp'); 
w.c=disan;imwrite(w.c,'w_c.bmp'); 
w.d=disi;imwrite(w.d,'w_d.bmp'); 
w.e=diwu;imwrite(w.e,'w_e.bmp'); 
w.f=diliu;imwrite(w.f,'w_f.bmp'); 
w.g=diqi;imwrite(w.g,'w_g.bmp'); 