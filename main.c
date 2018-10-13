/**
 * File: main.cpp
 * Author: Justin Siao
 */
#include <os.h>
#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <math.h>

#define SPRITE_SIZE 24

//------------------------------------------------------------------
int world_map[24][24] =
{
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,1,1,1,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,1,0,1,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,1,1,0,1,0,1,0,1,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,1,0,0,0,0,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,0,0,1,0,1,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1},
    {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
    {1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1},
    {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
    {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

char wall_sprite[16][16] =
{
    {1,1,1,1,1,2,3,3,2,1,1,1,1,2,1,1},
    {1,1,1,1,1,1,2,1,3,2,1,1,2,3,2,1},
    {1,1,1,1,1,2,3,1,1,3,2,2,3,1,2,1},
    {2,1,1,1,2,3,1,1,1,1,3,3,1,1,3,2},
    {3,2,2,2,3,3,1,1,1,1,1,1,1,1,1,3},
    {2,3,3,3,3,3,3,2,2,1,1,1,1,1,2,2},
    {2,2,3,1,3,2,2,3,3,2,2,1,2,2,1,1},
    {1,2,1,1,2,1,1,1,2,3,3,2,3,2,1,1},
    {1,2,1,1,2,1,1,1,2,3,3,2,3,2,1,1},
    {1,2,1,1,2,1,1,2,3,2,1,1,2,3,3,2},
    {2,3,1,1,3,2,2,3,2,1,1,2,3,3,2,3},
    {3,2,1,1,2,3,3,2,2,2,2,3,2,2,1,2},
    {2,3,2,2,3,2,3,3,2,2,3,2,1,1,1,1},
    {1,2,3,2,1,1,2,2,3,3,2,1,1,1,1,1},
    {1,2,3,2,1,1,1,1,2,3,2,1,1,1,1,1},
    {2,3,3,2,1,1,1,1,2,3,3,2,1,1,1,1}
};

char rune[SPRITE_SIZE][SPRITE_SIZE] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,4,4,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,4,4,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,4,4,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,4,4,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,4,4,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,4,4,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

char spectre[SPRITE_SIZE][SPRITE_SIZE] =
{
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,5,5,5,5,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,0,0,0,0,0,0,0,0,0}
};

short pallette[10];

double pixel_buffer[320];

//------------------------------------------------------------------
static struct player
{
    double x,y;
    double dir_x, dir_y;
} player = {11.5, 11.5, -1, 0};

static struct game
{
    double time_0, time_1;
    char running;
    char debug;
    char collide;
} game_data = {0, 0, 1, 0, 0};

struct video
{
    SDL_Surface *screen;
    nSDL_Font *font;
    double plane_x, plane_y;
} video;

struct sprite
{
    double x,y;
    char visible;
    char type;
    char (*sprite)[SPRITE_SIZE][SPRITE_SIZE];
} rune_sprite = {7.5, 11.5, 1, 0, &rune}, spectre_sprite = {1.5, 1.5, 1, 1, &spectre};


//------------------------------------------------------------------

void  game_init(void);

void  key_process(struct game *, struct player*, struct video *);

void  video_init(struct video *);
void  video_process(struct video *, struct player *);
void  video_render_wall(struct video *, struct player *);
char  video_render_sprites(struct video *, struct player *, struct sprite *);
void  video_wall_line(SDL_Surface *, int, int, int, int, int, int);
void  video_sprite_line(SDL_Surface *, int, int, int, int, int, char (*)[24][24], int);
short video_24_to_16(unsigned char, unsigned char, unsigned char);

char  collide(struct player*, struct sprite *);

void  debug_render(struct video *, nSDL_Font *);

//------------------------------------------------------------------

int main(int argc, char **argv) 
{
    if (argc) argc = 0;
    if (argv) argv = NULL;
    game_init();
    video_init(&video);
    SDL_FillRect(video.screen, NULL, SDL_MapRGB(video.screen->format, 0, 0, 0));
    while(game_data.running)
    {
        key_process(&game_data, &player, &video);
        video_process(&video, &player);
        sleep(10);
    }
    SDL_Quit();
    return 0;
}

void game_init(void)
{
    pallette[0] = video_24_to_16(  70,  95, 140); //Blue 1
    pallette[1] = video_24_to_16(  25,  55,  98); //Blue 2
    pallette[2] = video_24_to_16(  10,  28,  68); //Blue 3
    pallette[3] = video_24_to_16(  35,  49,  70); //Blue 4
    pallette[4] = video_24_to_16(  13,  27,  49); //Blue 5
    pallette[5] = video_24_to_16(   5,  14,  29); //Blue 6
    pallette[6] = video_24_to_16(   0, 127,   0); //Green
    pallette[7] = video_24_to_16(   0,   0,   0); //Black
    pallette[8] = video_24_to_16( 255, 255, 255); //White
}

void key_process(struct game *data, struct player *player, struct video *video)
{
    const double rotation = 0.1;
    const double move     = 0.1;
    if (isKeyPressed(KEY_NSPIRE_ESC))
    {
        data->running = 0;
    }
    if (isKeyPressed(KEY_NSPIRE_UP) || isKeyPressed(KEY_NSPIRE_8))
    {
        if (!world_map[(int)(player->x + player->dir_x * move)][(int)(player->y)])
        {
            player->x += player->dir_x * move;
        }
        if (!world_map[(int)(player->x)][(int)(player->y + player->dir_y * move)])
        {
            player->y += player->dir_y * move;
        }
    }
    if (isKeyPressed(KEY_NSPIRE_DOWN) || isKeyPressed(KEY_NSPIRE_2))
    {
        if (!world_map[(int)(player->x - player->dir_x * move)][(int)(player->y)])
        {
            player->x -= player->dir_x * move;
        }
        if (!world_map[(int)(player->x)][(int)(player->y - player->dir_y * move)])
        {
            player->y -= player->dir_y * move;
        }
    }
    if (isKeyPressed(KEY_NSPIRE_RIGHT) || isKeyPressed(KEY_NSPIRE_6))
    {
        double old_x   = player->dir_x;
        double old_y   = player->dir_y;
        double plane_x = video->plane_x;
        double plane_y = video->plane_y;
        player->dir_x  = old_x * cos(-rotation) - old_y * sin(-rotation);
        player->dir_y  = old_x * sin(-rotation) + old_y * cos(-rotation);
        video->plane_x =  plane_x * cos(-rotation) - plane_y * sin(-rotation);
        video->plane_y =  plane_x * sin(-rotation) + plane_y * cos(-rotation);
    }
    if (isKeyPressed(KEY_NSPIRE_LEFT) || isKeyPressed(KEY_NSPIRE_4))
    {
        double old_x   = player->dir_x;
        double old_y   = player->dir_y;
        double plane_x = video->plane_x;
        double plane_y = video->plane_y;
        player->dir_x  = old_x * cos(rotation) - old_y * sin(rotation);
        player->dir_y  = old_x * sin(rotation) + old_y * cos(rotation);
        video->plane_x =  plane_x * cos(rotation) - plane_y * sin(rotation);
        video->plane_y =  plane_x * sin(rotation) + plane_y * cos(rotation);
    }
}

void video_init(struct video * video_ptr)
{
    SDL_Init(SDL_INIT_VIDEO);
    video_ptr->screen = SDL_SetVideoMode(320, 240, has_colors ? 16 : 8, SDL_SWSURFACE);
    video_ptr->plane_x = 0.0f;
    video_ptr->plane_y = 0.6666f;
    video_ptr->font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 255, 255, 255);
}

void video_process(struct video *video_ptr, struct player *player_ptr)
{
    SDL_FillRect(video.screen, NULL, SDL_MapRGB(video.screen->format, 10, 10, 10));
    video_render_wall(video_ptr, player_ptr);
    video_render_sprites(video_ptr, player_ptr, &rune_sprite);
    game_data.debug = video_render_sprites(video_ptr, player_ptr, &spectre_sprite);
    game_data.collide = collide(player_ptr, &rune_sprite);
    debug_render(&video, video_ptr->font);
    SDL_Flip(video_ptr->screen);
}

void video_render_wall(struct video *video_ptr, struct player *player_ptr)
{
    for(int x = 0; x < 320; x ++)
    {
        double camera_x = (2 * x / 320.0f) - 1.0f;
        double ray_x    = player_ptr->dir_x + video_ptr->plane_x * camera_x;
        double ray_y    = player_ptr->dir_y + video_ptr->plane_y * camera_x;
        int    map_x    = (int) player_ptr->x;
        int    map_y    = (int) player_ptr->y;
        double delta_x  = fabs(1.0f/ray_x);
        double delta_y  = fabs(1.0f/ray_y);
        char   wall     = 0;
        char   side;
        int step_x, step_y;
        double side_x, side_y;
        double distance;
        if (ray_x < 0)
        {
            step_x = -1;
            side_x = (player_ptr->x - map_x) * delta_x;
        }
        else
        {
            step_x = 1;
            side_x = (map_x + 1.0 - player_ptr->x) * delta_x;
        }
        if (ray_y < 0)
        {
            step_y = -1;
            side_y = (player_ptr->y - map_y) * delta_y;
        }
        else
        {
            step_y = 1;
            side_y = (map_y + 1.0 - player_ptr->y) * delta_y;
        }
        while (!wall)
        {
            if (side_x < side_y)
            {
                side_x += delta_x;
                map_x  += step_x;
                side   = 0;
            }
            else
            {
                side_y += delta_y;
                map_y  += step_y;
                side   = 1;
            }
            wall = !!(world_map[map_x][map_y]);
        }
        if (!side) 
            distance = (map_x - player_ptr->x + (1 - step_x) / 2) / ray_x;
        else
            distance = (map_y - player_ptr->y + (1 - step_y) / 2) / ray_y;
        int line_height = (int)(240 / distance);
        int start = (-line_height / 2) + 120;
        if (start < 0) 
            start = 0;
        int end = (line_height / 2) + 120;
        if (end >= 240) 
            end = 239;
        // Calculate wall_x
        double wall_x;
        if (!side)
            wall_x = player_ptr->y + distance * ray_y;
        else
            wall_x = player_ptr->x + distance * ray_x;
        wall_x -= floor(wall_x);
        //x coordinate of the texture
        int tex_x = (int)(wall_x * 16.0f);
        if ((side == 0 && player_ptr->dir_x > 0) || (side == 1 && player_ptr->dir_y < 0))
            tex_x = 16 - tex_x - 1;
        video_wall_line(video_ptr->screen, x, start, end, tex_x, side, line_height);
        pixel_buffer[x] = distance;
    }
}
 
char video_render_sprites(struct video *video_ptr, struct player *player_ptr, struct sprite *sprite)
{
    char return_val = 0;
    if (sprite->visible)
    {
        double x = player_ptr->x;
        double y = player_ptr->y;

        double sprite_x = sprite->x - x;
        double sprite_y = sprite->y - y;

        double dir_x = player_ptr->dir_x;
        double dir_y = player_ptr->dir_y;

        double plane_x = video_ptr->plane_x;
        double plane_y = video_ptr->plane_y;

        double determinant = 1.0 / (plane_x * dir_y - dir_x * plane_y);
        double transform_x = determinant * (dir_y * sprite_x - dir_x * sprite_y);
        double transform_y = determinant * (-plane_y * sprite_x + plane_x * sprite_y);

        int screen_x = (int)((160) * (1 + transform_x / transform_y));
        int side     = abs((int)(240 / transform_y));

        int start_x  = -side / 2 + screen_x;
        int start_y  = -side / 2 + 120;
        int end_x    =  side / 2 + screen_x;
        int end_y    =  side / 2 + 120;

        if ( start_x < 0) start_x = 0;
        if ( start_y < 0) start_y = 0;
        if ( end_x   > 319) end_x = 319;
        if ( end_y   > 239) end_y = 239;
        
        for (int stripe = start_x; stripe < end_x; stripe++)
        {
            int tex_x = (int)(256 * (stripe - (-side / 2 + screen_x)) * SPRITE_SIZE / side) / 256;
            if (transform_y > 0 && stripe > 0 && stripe < 320 && transform_y < pixel_buffer[stripe] )
            {
                 video_sprite_line(video_ptr->screen, stripe, start_y, end_y, tex_x, sprite->type, sprite->sprite, side);
                 return_val = 1;
            }
        }
    }
    return return_val;
}

void video_sprite_line(SDL_Surface *surface, int x, int start, int end, int tex_x, int type, char (*sprite)[SPRITE_SIZE][SPRITE_SIZE], int line_height)
{
    if (type) type = 0;
    for (int y = start; y < end; y++)
    {
        int d = y * 256 - 240 * 128 + line_height * 128;
        int tex_y = ((d * SPRITE_SIZE) / line_height) / 256;
        char color = (*sprite)[tex_y][tex_x];
        int c = pallette[9];
        switch (color)
        {
            case 1:
                c = pallette[0];
                break;
            case 2:
                c = pallette[1];
                break;
            case 3:
                c = pallette[2];
                break;
            case 4:
                c = pallette[6];
                break;
            case 5:
                c = pallette[7];
                break;
            case 6:
                c = pallette[8];
                break;
            case 7:
                c = pallette[9];
                break;
            default:
                color = 0;
        }
        if (color)
        {
            nSDL_SetPixel(surface, x, y, c);
        }
    }
}

void video_wall_line(SDL_Surface *surface, int x, int start, int end, int tex_x, int side, int line_height)
{
    for (int y = start; y < end; y++)
    {
        int d = y * 256 - 240 * 128 + line_height * 128;
        int tex_y = ((d * 16) / line_height) / 256;
        int color = wall_sprite[tex_y][tex_x];
        int xcolor;
        if (side)
        {
            switch (color)
            {
            case 1:
                xcolor = pallette[0];
                break;
            case 2:
                xcolor = pallette[1];
                break;
            case 3:
                xcolor = pallette[2];
                break;
            }
        }
        else
        {
            switch (color)
            {
            case 1:
                xcolor = pallette[3];
                break;
            case 2:
                xcolor = pallette[4];
                break;
            case 3:
                xcolor = pallette[5];
                break;
            }
        }
        nSDL_SetPixel(surface, x, y, xcolor);
    }
}

// Borrowed from Lucas Galand at:
// https://www.lucasgaland.com/24-bit-16-bit-color-converter-tool-for-embedded-lcd-guis/

short video_24_to_16(unsigned char red, unsigned char green, unsigned char blue)
{
    unsigned int r5 = (red * 249 + 1014) >> 11;
    unsigned int g6 = (green * 253 + 505) >> 10;
    unsigned int b5 = (blue * 249 + 1014) >> 11;

    return (r5<<11) | (g6<<5) | b5;
}

void debug_render(struct video *video, nSDL_Font *font)
{
    static int y = 0;
    char debug[32];
    snprintf(debug, 32, "See this: %d", y);
    nSDL_DrawString(video->screen, font, 10, 10, "Justin was Here. \x1");
    nSDL_DrawString(video->screen, font, 10, 0, debug);
    snprintf(debug, 32, "Player x: %f", player.x);
    nSDL_DrawString(video->screen, font, 10, 20, debug);
    snprintf(debug, 32, "Player y: %f", player.y);
    nSDL_DrawString(video->screen, font, 10, 30, debug);
    snprintf(debug, 32, "spectre: %s", ((game_data.debug)?"TRUE":"FALSE"));
    nSDL_DrawString(video->screen, font, 10, 40, debug);
    snprintf(debug, 32, "spectre: %s", ((game_data.collide)?"TRUE":"FALSE"));
    nSDL_DrawString(video->screen, font, 10, 50, debug);
    y++;
}

char collide(struct player* player, struct sprite *sprite)
{
    if (sprite->visible)
    {
        double dx = fabs(player->x - sprite->x);
        double dy = fabs(player->y - sprite->y);
        double distance = dx * dx + dy * dy ;
        if (distance < 0.0625)
        {
            return 1;
        }
    }
    return 0;
}
