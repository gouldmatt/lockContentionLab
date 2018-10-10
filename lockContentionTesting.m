method1 = zeros(1,100);
method2 = zeros(1,100);
method3 = zeros(1,100);

% Run each method k times 
for k = 1 : 100 
    [~,outM1] = system('./method1');
    method1(1,k) = str2double(outM1); 
end 

for k = 1 : 100 
    [~,outM2] = system('./method2');
    method2(1,k) = str2double(outM2); 
end 

for k = 1 : 100
    [~,outM3] = system('./method3');
    method3(1,k) = str2double(outM3); 
end 

% construct graphs 
figure
h1 = scatter(method1,1:100,'b','o');
hold on
h2 = scatter(method2,1:100,'k','+');
hold on
h3 = scatter(method3,1:100,'g','p');
legend([h1,h2,h3], 'Method 1', 'Method 2', 'Method 3')
ylabel('Run #');
xlabel('Time milliseconds');
xlim([0,100]); 
hold off 

%{
figure
pd = makedist('Normal');
pdf_normal = pdf(pd,method1);
plot(method1,pdf_normal,'LineWidth',2);
%}
figure
norm(method1); 

figure
norm(method2);


figure
norm(method3);







