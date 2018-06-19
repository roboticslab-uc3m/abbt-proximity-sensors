close all;
clc;

delete(instrfind({'Port'},{'COM3'}));
arduino = serial('COM3');
arduino.BaudRate = 9600;

fopen(arduino);

figure
xlabel('Time (s)');
ylabel('Cubos (ud)');
grid on ;
hold on;

tiempo_prueba_BBT = 60;

t_fin = 0;
detectado = 0;
t_parcial = 0;
t_aux = 0;

n_cubos = zeros(1, detectado+1);
tiemp = zeros(1, detectado+1);
parciales = zeros(1, detectado+1);
parciales_aux = zeros(1, detectado+1);

detectado = fscanf(arduino,'%d')';

if detectado == -1
tic
end

while detectado ~= -2
%%while t_fin <= tiempo_prueba_BBT
    detectado = fscanf(arduino,'%d')';
    parciales_aux(detectado) = t_fin;
    t_fin = toc;

    ylim([0 detectado+5]);
    xlim([0 t_fin+5]);
    
    %%t_parcial = toc;
      
    n_cubos(detectado) = detectado;
    tiemp(detectado) = t_fin;
    
    
    
    plot(tiemp(detectado),n_cubos(detectado),'X-r')
    drawnow; 
    parciales = tiemp - parciales_aux;

   
end


fclose(arduino);
delete(arduino);

%{
figure
subplot(2,1,1)
xlabel('Time (s)');
ylabel('Cubos (ud)');
grid on ;
hold on;
plot(tiemp, n_cubos,'s-r');

subplot(2,1,2)
xlabel('Cubos (ud)');
ylabel('Tiempo parcial (s)');
grid on ;
hold on;
plot(n_cubos, parciales,'s-b');
%}


%%plot(x(n_cubos),y(n_cubos),'X-r');
%%plot(x(n_cubos),z(n_cubos),'X-r');
