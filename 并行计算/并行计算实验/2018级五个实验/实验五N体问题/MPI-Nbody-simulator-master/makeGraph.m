N=bodypos(1,1);
Time=bodypos(1,2);
xmax=max(bodypos(2:N*Time+1,2));
xmin=min(bodypos(2:N*Time+1,2));
ymax=max(bodypos(2:N*Time+1,3));
ymin=min(bodypos(2:N*Time+1,3));
zmax=max(bodypos(2:N*Time+1,4));
zmin=min(bodypos(2:N*Time+1,4));

for i=1:Time
    x = bodypos(N*(i-1)+2:N*(i-1)+N,2);
    y = bodypos(N*(i-1)+2:N*(i-1)+N,3);
    z = bodypos(N*(i-1)+2:N*(i-1)+N,4);
    r = bodypos(N*(i-1)+2:N*(i-1)+N,5);
    scatter3(x,y,z,r,'filled');
    axis([xmin xmax ymin ymax zmin zmax]) 
    pause();
end