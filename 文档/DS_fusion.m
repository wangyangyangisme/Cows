function x=DS_fusion(x,y)

% 功能：融合x,y两行向量(经典Dempster-Shafer组合公式)
% x,y的格式形如[m1 m2 m3, ... , mk, m(全集), m(空集)]
% 要求m1 m2 m3 ...之间互相无交集
% m(全集)可不为0，表示不确定度
% m(空集)肯定是0

%n为行数
%m为列数
[nx,mx]=size(x);
if 1~=nx
    disp('x应为行向量');
    return;
end

[ny,my]=size(y);
if 1~=ny
    disp('y应为行向量');
    return;
end

if mx~=my
    disp('x,y列数应相等');
    return;
end

temp=0;
for i=1:mx-1
    
    if i==mx-1
        x(1,i)=x(1,i)*y(1,i);  %对全集的特殊处理
    else
        x(1,i)=x(1,i)*y(1,i)+x(1,i)*y(1,mx-1)+y(1,i)*x(1,mx-1);
    end
    temp=temp+x(1,i);
end

for i=1:mx-1
    x(1,i)=x(1,i)/temp;
end

x(1,mx)=0;
    