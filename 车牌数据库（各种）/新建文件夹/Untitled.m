N=2;  %  滤波器长度（需要调整，必须是偶数）
A=-1/sqrt(2*pi);  %  幅度
m=1.0;
delta=2^m;
for index_x=1:N
    for index_y=1:N
        x=index_x-(N+1)/2
        y=index_y-(N+1)/2
        phi_x(index_x,index_y)=A*(x/delta^2).*exp(-(x.*x+y.*y)/(2*delta^2));
        phi_y(index_x,index_y)=A*(y/delta^2).*exp(-(x.*x+y.*y)/(2*delta^2));
    end
end;