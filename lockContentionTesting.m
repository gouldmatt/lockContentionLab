method1 = zeros(1,10);
method2 = zeros(50,1);
method3 = zeros(50,1);

% Run each method k times 
for k = 1 : 10 
    [~,outM1] = system('./method1');
    method1(1,k) = str2double(outM1); 
end 

%{
for k = 1 : 5 
    [~,outM2] = system('./method2');
    method2(k,1) = str2double(outM2); 
end 

for k = 1 : 5 
    [~,outM3] = system('./method3');
    method3(k,1) = str2double(outM3); 
end 
%}

% construct graphs 
scatter(1:10,method1)
xlabel('Run #');
ylabel('Time milliseconds');

%{
pd = makedist('Normal');
pdf_normal = pdf(pd,method1)
plot(method1,pdf_normal,'LineWidth',2)
%}



