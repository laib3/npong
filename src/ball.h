typedef struct bll *Ball;

Ball ball_init();
void ball_destroy(Ball b);
void set_x(Ball b, int val);
void set_y(Ball b, int val);
void set_xy(Ball b, int x, int y);
void set_dir_x(Ball b, int dir);
void set_dir_y(Ball b, int dir);
void get_xy(Ball b, int *x, int *y);
int get_x(Ball b);
int get_y(Ball b);
int get_dir_x(Ball b);
int get_dir_y(Ball b);
