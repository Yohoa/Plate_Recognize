A=imread('A.jpg');
rgb1= imread('1.jpg');
rgb=double(rgb1);
hsv=rgb2hsv(rgb);
gray = rgb2gray(rgb1);%rgb2grayת���ɻҶ�ͼ
% figure,imshow(gray),title('ԭʼ�ڰ�ͼ��');
s=strel('disk',13);                     %strel����
Bgray=imopen(gray,s);                  %ͼ������
% figure,imshow(Bgray);title('����ͼ��'); %�������ͼ��
Egray=imsubtract(gray,Bgray);            %����ͼ���
% figure,imshow(Egray);title('��ǿ�ڰ�ͼ��');%����ڰ�ͼ��
fmax1=double(max(max(Egray)));        %Egray�����ֵ�����˫������
fmin1=double(min(min(Egray)));         %Egray����Сֵ�����˫������
level=(fmax1-(fmax1-fmin1)/1.3)/255;     %��������ֵ
bw22=im2bw(Egray,level);               %ת��ͼ��Ϊ������ͼ��
bw2=double(bw22);
%   figure,imshow(bw22);title('���ƶ�ֵ��ͼ��');
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
              figure;title('���Ʒָ��ͼ��');
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
