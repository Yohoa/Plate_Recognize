%Step1 ��ȡͼ��   װ��������ɫͼ����ʾԭʼͼ��
Scolor = imread('cb36.jpg');%imread������ȡͼ���ļ�

%����ɫͼ��ת��Ϊ�ڰײ���ʾ
Sgray = rgb2gray(Scolor);%rgb2grayת���ɻҶ�ͼ
figure,imshow(Scolor),title('ԭʼ��ɫͼ��');%figure����ͬʱ��ʾ����ͼ
figure,imshow(Sgray),title('ԭʼ�ڰ�ͼ��');


%Step2 ͼ��Ԥ����   ��Sgray ԭʼ�ڰ�ͼ����п������õ�ͼ�񱳾�
s=strel('disk',13);%strel����
Bgray=imopen(Sgray,s);%��sgray sͼ��
figure,imshow(Bgray);title('����ͼ��');%�������ͼ��
%��ԭʼͼ���뱳��ͼ������������ǿͼ��
Egray=imsubtract(Sgray,Bgray);%����ͼ���
figure,imshow(Egray);title('��ǿ�ڰ�ͼ��');%����ڰ�ͼ��

%Step3 ȡ�������ֵ����ͼ���ֵ��
fmax1=double(max(max(Egray)));%egray�����ֵ�����˫������
fmin1=double(min(min(Egray)));%egray����Сֵ�����˫������
level=(fmax1-(fmax1-fmin1)/3)/255;%��������ֵ
bw22=im2bw(Egray,level);%ת��ͼ��Ϊ������ͼ��
bw2=double(bw22);
figure,imshow(bw2);title('ͼ���ֵ��');%�õ���ֵͼ��


%Step4 �Եõ���ֵͼ�������ղ��������˲�
grd=edge(bw2,'canny')%��canny����ʶ��ǿ��ͼ���еı߽�
figure,imshow(grd);title('ͼ���Ե��ȡ');%���ͼ���Ե
bg1=imclose(grd,strel('rectangle',[5,19]));%ȡ���ο�ı�����

figure,imshow(bg1);title('ͼ�������[5,19]');%����������ͼ��
bg3=imopen(bg1,strel('rectangle',[5,19]));%ȡ���ο�Ŀ�����
figure,imshow(bg3);title('ͼ������[5,19]');%����������ͼ��
bg2=imopen(bg3,strel('rectangle',[19,1]));%ȡ���ο�Ŀ�����
figure,imshow(bg2);title('ͼ������[19,1]');%����������ͼ��

