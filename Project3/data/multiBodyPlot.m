load positions.dat;         %  read data 
figure
hold on;

view(45,45);
max_val = max(max(positions(:,1:3:end)));
axis([-max_val max_val -max_val max_val -max_val max_val]);
for i=4:3:28
    plot3(positions(:,i), positions(:,i+1), positions(:,i+2));
end

h = plot3(positions(1,:), positions(1,:),positions(1,:), '.k');


for i=1:10:length(positions(:,1)) 
    set(h, 'XData', positions(i,1:3:end), 'YData', positions(i,2:3:end),'ZData', positions(i,3:3:end));
    drawnow;
end

axis equal