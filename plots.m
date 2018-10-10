figure(1)
h1 = scatter(method1,1:200,'b','o');
hold on
h3 = scatter(method3,1:200,'g','p');
legend([h1,h3], 'Method 1','Method 3')
ylabel('Run #');
xlabel('Time milliseconds');
xlim([0,200]); 
hold off 
title('Method 1 vs Method 3')

figure(2)
h1 = scatter(method1,1:200,'b','o');
hold on
h2 = scatter(method2,1:200,'k','+');
hold on
h3 = scatter(method3,1:200,'b','o');
legend([h1,h2], 'Method 1 & Method 3', 'Method 2')
ylabel('Run #');
xlabel('Time milliseconds');
hold off 
title('Method 1 and Method 3 vs Method 2 ')

figure(6)
histfit(method1);
title('Method 1')

figure(7)
histfit(method2);
title('Method 2')

figure(8)
histfit(method3);
title('Method 3')



