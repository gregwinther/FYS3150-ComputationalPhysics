load twosystem.dat;         %  read data 

x_sun = twosystem(:,1);     
y_sun = twosystem(:,2);   

x_earth = twosystem(:,4);    
y_earth = twosystem(:,5);    

plot(x_earth,y_earth,x_sun,y_sun);