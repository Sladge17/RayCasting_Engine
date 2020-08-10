# WOLF3D
Движок 2,5D - воспроизведение движка Wolfinstain3D

Сборка:
1.
Для линукс утановить библиотеку SDL2:
  
  
  #install sdl2
  
  sudo apt install libsdl2-dev libsdl2-2.0-0 -y;
  
  
  #install sdl image(for load images)
  
  sudo apt install libjpeg-dev libwebp-dev libtiff5-dev libsdl2-image-dev libsdl2-image-2.0-0 -y;


  #install sdl mixer(for load musics)
  
  sudo apt install libmikmod-dev libfishsound1-dev libsmpeg-dev liboggz2-dev libflac-dev libfluidsynth-dev libsdl2-mixer-dev libsdl2-mixer-2.0-0 -y;


  #install sdl ttf(for load fonts)
  
  sudo apt install libfreetype6-dev libsdl2-ttf-dev libsdl2-ttf-2.0-0 -y;


Для macos библиотека SDL2 уже собрана в frameworks


2.

make all


Запуск:


запуск игры:

./WOLF


запуск редактора карт:

./WOLF editor
