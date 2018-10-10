method1 = zeros(1,200);
method2 = zeros(1,200);
method3 = zeros(1,200);

% Run each method k times 
for k = 1 : 200 
    [~,outM1] = system('./method1');
    method1(1,k) = str2double(outM1); 
end 

for k = 1 : 200
    [~,outM2] = system('./method2');
    method2(1,k) = str2double(outM2); 
    k
end 

for k = 1 : 200
    [~,outM3] = system('./method3');
    method3(1,k) = str2double(outM3); 
end 

% construct graphs 
figure(1)
h1 = scatter(method1,1:200,'b','o');
hold on
h2 = scatter(method2,1:200,'k','+');
hold on
h3 = scatter(method3,1:200,'g','p');
legend([h1,h2,h3], 'Method 1', 'Method 2', 'Method 3')
ylabel('Run #');
xlabel('Time milliseconds');
xlim([0,200]); 
hold off 

%{
figure
pd = makedist('Normal');
pdf_normal = pdf(pd,method1);
plot(method1,pdf_normal,'LineWidth',2);
%}

figure(2)
histogram(method1); 

figure(3)
histogram(method2);

figure(4)
histogram(method3);

save('351 Data')








