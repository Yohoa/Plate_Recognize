BW2=www;
A=imread('image.jpg');
R=A(:,:,1);
G=A(:,:,2);
B=A(:,:,3);
k=1;
g=1;
[y,x,z]=size(A);%y行，x列

cp_bluey=zeros(x*y,1);
cp_bluex=zeros(x*y,1);

cp_briy=zeros(x*y,1);
cp_brix=zeros(x*y,1);

for i=1:y-1       %i行
    for j=1:x-1
if(A(i,j,2)>A(i,j,1) & A(i,j,3)>A(i,j,2))  %i行，j列 简单的检测蓝色
        cp_bluey(k)=i;
        cp_bluex(k)=j;
        k=k+1;
    else
        cp_briy(g)=i;
        cp_brix(g)=j;
        g=g+1;
end
    end
end
figure(1);
imshow(A);
hold on;
plot(cp_bluex(1:k),cp_bluey(1:k),'r.')
plot(cp_brix(1:k),cp_briy(1:k),'y.')