function [PY2,PY1,PX2,PX1]=chepai_fenge(I5)
[y,x,z]=size(I5);
myI=double(I5);
%begin����ɨ��
Y_threshlow=5; %�����ֵ����Ҫ����������ȡ�Ĳ�ͼ������
X_firrectify=5;
%=== Y ����===��������Ѱ�ҵ�һ��1ֵ���ش���5������Ϊˮƽ�������ֽ��ߣ���������Ѱ�ҵ���һ��1ֵ����������5��Ϊ�Ҳ�ֽ���
Blue_y=zeros(y,1);
for i=1:y
    for j=1:x
        if(myI(i,j,1)==1)%���myI(i,j,1)��myIͼ��������Ϊ(i,j)�ĵ�Ϊ��ɫ
         %��Blue_y����Ӧ�е�Ԫ��white_y(i,1)ֵ��1
           Blue_y(i,1)= Blue_y(i,1)+1;     % ��ɫ���ص�ͳ��                    
        end  
    end       
end
        [temp MaxY]=max(Blue_y);% Y����������ȷ�� temp(������):�������У������ۻ����ص� MaxY�����������У�:�������������
         PY1=MaxY;%�����������и���PY1
        while ((Blue_y(PY1,1)>=Y_threshlow)&&(PY1>1))%�ҵ�ͼƬ�ϱ߽�
            PY1=PY1-1;
        end 
       
        %PY1���洢�����ϱ߽�ֵ
        PY2=MaxY;
        while ((Blue_y(PY2,1)>=Y_threshlow)&&(PY2<y))%��ֵΪ5
             PY2=PY2+1;
        end
       PY1, PY2 %ԭʼͼ��I�н�ȡ����������PY1��PY2֮��Ĳ���
    figure(1),imshow(Blue_y),title('y����ȷ��');
    pause(2);
    %==============X ����===============================
        X_threshhigh=(PY2-PY1)/11;%�����ֵ����Ҫ����������ȡ�Ĳ�ͼ������,�ʵ���߿ɿ����ţ�����Сͼ���ճɼ���̫��
        Blue_x=zeros(1,x);             % ��һ��ȷ��X����ĳ�������
        for j=1:x
            for i=PY1:PY2
                if(myI(i,j,1)==1)
                 Blue_x(1,j)= Blue_x(1,j)+1;               
                end  
            end       
        end
        [temp MaxX]=max(Blue_x);
        PX1=MaxX-6*(PY2-PY1);
        if  PX1<=1
            PX1=1;
        end
        while ((Blue_x(1,PX1)<=X_threshhigh)&&(PX1<x))%��ֵ
              PX1=PX1+1;
        end               %ȷ����X���������   
        PX2=MaxX+6*(PY2-PY1);
        if  PX2>=x
            PX2=x;
        end
        while ((Blue_x(1,PX2)<=X_threshhigh)&&(PX2>PX1))%��ֵ
               PX2=PX2-1;
        end            %ȷ����X�������յ�
        PX1 ,PX2
    figure(2),imshow(Blue_x),title('X����ȷ��');    