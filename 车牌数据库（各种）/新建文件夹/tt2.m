%�Զ�λ����Ԥ����ȥ���߿��í�� 
clear all;clc; 
f=imread('A.jpg');%���붨λ��ĳ��� 
% figure(1),imshow(f); 
%threshold=graythresh(f);%��ֵ����ֵ 
f1=im2bw(f,0.75);%��ֵ�� 
 figure(2),imshow(f1);%��ʾ��ֵ������ͼ�� 
[x,y]=size(f1); 
m=zeros(x,1); 
for i=1:x 
    for j=1:y 
        if(f1(i,j)==1)          
            m(i,1)=m(i,1)+1;%��ɨ��ͳ��ÿ�а�ɫ���ص���� 
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
            f1(i,j)=0;%ȥ���ϱ߿���ϱߵ�í�� 
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
            f1(i,j)=0;%ȥ�������±߿� 
        end 
    end 
end 
figure(3),imshow(f1);%��ʾȥ�����±߿��ĳ��� 
n=zeros(1,y); 
for j=1:y 
    for i=1:x 
        if f1(i,j)==1 
           n(1,y)=n(1,y)+1;%��ɨ��ͳ��ÿ�а�ɫ���ص���� 
        end 
    end 
end 
for j=1:y/25 
    for i=1:x 
        if f1(i,j)==1 
           f1(i,j)=0;%ȥ��������߿� 
        end 
    end 
end 
% figure(4),imshow(f1);%��ʾȥ����߿��ĳ��� 
for j=round(y-y/25):y 
    for i=1:x 
        if f1(i,j)==1 
           f1(i,j)=0;%ȥ�������ұ߿� 
        end 
    end 
end 
figure(5),imshow(f1);%��ʾȥ���ұ߿��ĳ��� 
%�ַ��ָ���� 
p=zeros(1,y); 
for j=1:y 
    for i=1:x 
        if f1(i,j)==1 
           p(1,j)=p(1,j)+1;%��ɨ��ͳ��ÿ�а�ɫ���ص���� 
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
figure(6),imshow(diyi);%��ʾ��һ���ַ� 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y/3.5)) 
    py1=py1+1; 
end 
dier=f1(:,py2:py1); 
figure(7),imshow(dier);%��ʾ�ڶ����ַ� 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y/2)) 
    py1=py1+1; 
end 
disan=f1(:,py2:py1); 
figure(8),imshow(disan);%��ʾ�������ַ� 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y/1.5)) 
    py1=py1+1; 
end 
disi=f1(:,py2:py1); 
figure(9),imshow(disi);%��ʾ���ĸ��ַ� 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y)) 
    py1=py1+1; 
end 
diwu=f1(:,py2:py1); 
figure(10),imshow(diwu);%��ʾ������ַ� 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y)) 
    py1=py1+1; 
end 
diliu=f1(:,py2:py1); 
figure(11),imshow(diliu);%��ʾ�������ַ� 
while (p(1,py1)<=2) 
    py1=py1+1; 
end 
py2=py1; 
while (p(1,py1)>=1)&&(py1<round(y)) 
    py1=py1+1; 
end 
diqi=f1(:,py2:py1); 
figure(12),imshow(diqi);%��ʾ���߸��ַ� 
w.a=diyi;imwrite(w.a,'w_a.bmp'); 
w.b=dier;imwrite(w.b,'w_b.bmp'); 
w.c=disan;imwrite(w.c,'w_c.bmp'); 
w.d=disi;imwrite(w.d,'w_d.bmp'); 
w.e=diwu;imwrite(w.e,'w_e.bmp'); 
w.f=diliu;imwrite(w.f,'w_f.bmp'); 
w.g=diqi;imwrite(w.g,'w_g.bmp'); 