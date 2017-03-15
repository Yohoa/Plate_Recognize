Y=imread('cb36.jpg');
imshow(Y);
R=Y(:,:,1);
G=Y(:,:,2);
B=Y(:,:,3);
[m,n]=size(R);
for i=1:m
    for j=1:n
      if (R(i,j)>8&&R(i,j)<74)&&(G(i,j)>25&&G(i,j)<129)&&(B(i,j)>82&&B(i,j)<219)
        A8(i,j)=1;
      else
        A8(i,j)=0;
      end
    end
end
A=medfilt2(A8);
se=strel('disk',5,4);
A8=imdilate(A,se);
A8=imfill(A8,'holes');
A8=bwareaopen(A8,500);
figure;imshow(A8);
R(~A8)=0;
G(~A8)=0;
B(~A8)=0;
A8=cat(3,R,G,B);
figure,imshow(A8);