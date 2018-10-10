method1 = zeros(1,10);
method2 = zeros(1,10);
method3 = zeros(1,10);

% Run each method k times 
for k = 1 : 10 
    [~,outM1] = system('./method1');
    method1(1,k) = str2double(outM1); 
end 

for k = 1 : 10 
    [~,outM2] = system('./method2');
    method2(1,k) = str2double(outM2); 
end 

for k = 1 : 10
    [~,outM3] = system('./method3');
    method3(1,k) = str2double(outM3); 
end 

% construct graphs 
figure(1)
h1 = scatter(method1,1:10,'b','o');
hold on
h2 = scatter(method2,1:10,'k','+');
hold on
h3 = scatter(method3,1:10,'g','p');
legend([h1,h2,h3], 'Method 1', 'Method 2', 'Method 3')
ylabel('Run #');
xlabel('Time milliseconds');
xlim([0,10]); 
hold off 

%{
figure
pd = makedist('Normal');
pdf_normal = pdf(pd,method1);
plot(method1,pdf_normal,'LineWidth',2);
%}
norm = normpdf(x,0,1);

figure(2)
histogram(method1); 

figure(3)
histogram(method2);

figure(4)
histogram(method3);

figure(5)
plot(method1,norm); 

figure(6)
plot(method2,norm); 

figure(7)
plot(method3,norm); 








