clc
clear
close all

I=imread('3.jpg');
subplot(3,2,1);imshow(I), title('ԭʼͼ��');
I_gray=rgb2gray(I);
subplot(3,2,2),imshow(I_gray),title('�Ҷ�ͼ��');

%======================   ��̬ѧԤ���� ======================
I_edge=edge(I_gray,'sobel');
subplot(3,2,3),imshow(I_edge),title('��Ե����ͼ��');
se=[1;1;1]; 
I_erode=imerode(I_edge,se);   
subplot(3,2,4),imshow(I_erode),title('��ʴ���Եͼ��');
se=strel('rectangle',[25,25]);  
I_close=imclose(I_erode,se);            %ͼ��պϡ����ͼ��
subplot(3,2,5),imshow(I_close),title('����ͼ��');
I_final=bwareaopen(I_close,2000);       %ȥ�����ŻҶ�ֵС��2000�Ĳ���
subplot(3,2,6),imshow(I_final),title('��̬�˲���ͼ��');


%==========================   ���Ʒָ�    =============================
I_new=zeros(size(I_final,1),size(I_final,2));
location_of_1=[];
for i=1:size(I_final,1)                 %Ѱ�Ҷ�ֵͼ���а׵ĵ��λ��
    for j=1:size(I_final,2)
        if I_final(i,j)==1;
            newlocation=[i,j];
            location_of_1=[location_of_1;newlocation];   
        end
    end
end
mini=inf;maxi=0;
for i=1:size(location_of_1,1)
%Ѱ�����а׵��У�x������y����ĺ������С���������λ��
    temp=location_of_1(i,1)+location_of_1(i,2);
    if temp<mini
        mini=temp;
        a=i;
    end
    if temp>maxi
        maxi=temp;
        b=i;
    end
end
first_point=location_of_1(a,:);        %����С�ĵ�Ϊ���Ƶ����Ͻ�
last_point=location_of_1(b,:);         %�����ĵ�Ϊ���Ƶ����½�
x1=first_point(1)+4;                %����ֵ����
x2=last_point(1)-4;
y1=first_point(2)+4;
y2=last_point(2)-4;
I_plate=I(x1:x2,y1:y2);
I_plate=im2bw(I_plate);              %��OTSU�㷨�Էָ���ĳ��ƽ�������Ӧ��ֵ������
%%
I_plate=bwareaopen(I_plate,50);
figure,imshow(I_plate),title('������ȡ')          %�������ճ���
%%  �ַ��ָ�
X=[];                               %�������ˮƽ�ָ��ߵĺ�����
flag=0;
for j=1:size(I_plate,2)    
    sum_y=sum(I_plate(:,j));
    if logical(sum_y)~=flag         %�к��б仯ʱ����¼�´���
        X=[X j];
        flag=logical(sum_y);
    end
end
for n=1:7                          
    char=I_plate(:,X(2*n-1):X(2*n)-1); %���дַָ�
    for i=1:size(char,1)            %������forѭ���Էָ��ַ������½��вü�
        if sum(char(i,:))~=0
            top=i;
            break
        end
    end
    for i=1:size(char,1)
        if sum(char(size(char,1)-i,:))~=0
            bottom=size(char,1)-i;
            break
        end
    end
    char=char(top:bottom,:);
    subplot(2,4,n);imshow(char);
    char=imresize(char,[32,16],'nearest'); %��һ��Ϊ32*16�Ĵ�С���Ա�ģ��ƥ��
    eval(strcat('Char_',num2str(n),'=char;'));  %���ָ���ַ�����Char_i��
end
