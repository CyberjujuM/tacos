#ifndef APPS_H
#define APPS_H

int main_fiinou(int argc, char* argv[] );
int launch_pres();
int launch_matrix();
int test_gui();

int semaphore_task(int argc, char** argv );
int test_semaphores();
void test_kmalloc();
void test_memory_reserve_page_frame();
int calc_pi();
int pi(int argc , char** argv );
int test_task1(int argc, char** argv);
int test_task();
int test_mouse_task();
int test_mouse();
int test_scanf();
int test_fgets();
int test_fputs();
int test_fwrite();
int test_fread();
int test_write_serial();
int test_read_serial();
int debug_fat();
int test_ansi();
int snake_main();
int cube_launcher();
int noxeyes(); 
int test_elf();
int test_ctype();
int test_stdio();

#endif //APPS_H
