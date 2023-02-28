#include"define.h"
void* alignedmalloc(size_t size)
//内存对齐函数 
{
  void* ret;
  posix_memalign(&ret, 64, size);
  return ret;
}
void generate_seeds(level_hash *level)
//生成该hash的两个种子
{
    srand(time(NULL));
    do
    {
        level->f_seed = rand();
        level->s_seed = rand();
        level->f_seed = level->f_seed << (rand() % 63);
        level->s_seed = level->s_seed << (rand() % 63);
    } while (level->f_seed == level->s_seed);
}



