#include <os.h>
#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <math.h>

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
    {0x01,0x01,0x01,0x01,0x01,0x02,0x03,0x03,0x02,0x01,0x01,0x01,0x01,0x02,0x01,0x01},
    {0x01,0x01,0x01,0x01,0x01,0x01,0x02,0x01,0x03,0x02,0x01,0x01,0x02,0x03,0x02,0x01},
    {0x01,0x01,0x01,0x01,0x01,0x02,0x03,0x01,0x01,0x03,0x02,0x02,0x03,0x01,0x02,0x01},
    {0x02,0x01,0x01,0x01,0x02,0x03,0x01,0x01,0x01,0x01,0x03,0x03,0x01,0x01,0x03,0x02},
    {0x03,0x02,0x02,0x02,0x03,0x03,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x01,0x03},
    {0x02,0x03,0x03,0x03,0x03,0x03,0x03,0x02,0x02,0x01,0x01,0x01,0x01,0x01,0x02,0x02},
    {0x02,0x02,0x03,0x01,0x03,0x02,0x02,0x03,0x03,0x02,0x02,0x01,0x02,0x02,0x01,0x01},
    {0x01,0x02,0x01,0x01,0x02,0x01,0x01,0x01,0x02,0x03,0x03,0x02,0x03,0x02,0x01,0x01},
    {0x01,0x02,0x01,0x01,0x02,0x01,0x01,0x01,0x02,0x03,0x03,0x02,0x03,0x02,0x01,0x01},
    {0x01,0x02,0x01,0x01,0x02,0x01,0x01,0x02,0x03,0x02,0x01,0x01,0x02,0x03,0x03,0x02},
    {0x02,0x03,0x01,0x01,0x03,0x02,0x02,0x03,0x02,0x01,0x01,0x02,0x03,0x03,0x02,0x03},
    {0x03,0x02,0x01,0x01,0x02,0x03,0x03,0x02,0x02,0x02,0x02,0x03,0x02,0x02,0x01,0x02},
    {0x02,0x03,0x02,0x02,0x03,0x02,0x03,0x03,0x02,0x02,0x03,0x02,0x01,0x01,0x01,0x01},
    {0x01,0x02,0x03,0x02,0x01,0x01,0x02,0x02,0x03,0x03,0x02,0x01,0x01,0x01,0x01,0x01},
    {0x01,0x02,0x03,0x02,0x01,0x01,0x01,0x01,0x02,0x03,0x02,0x01,0x01,0x01,0x01,0x01},
    {0x02,0x03,0x03,0x02,0x01,0x01,0x01,0x01,0x02,0x03,0x03,0x02,0x01,0x01,0x01,0x01}
};

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
} game_data = {0, 0, 1};

struct video
{
    SDL_Surface *screen;
    nSDL_Font *font;
    double plane_x, plane_y;
} video;

//------------------------------------------------------------------

void  key_process(struct game *, struct player*, struct video *);

void  video_init(struct video *);
void  video_process(struct video *, struct player *);
void  video_render_wall(struct video *, struct player *);
void  video_vertical_line(SDL_Surface *, int, int, int, int, int);
short video_24_to_16(unsigned char, unsigned char, unsigned char);

void  debug_render(struct video *, nSDL_Font *);

//------------------------------------------------------------------

int main(int argc, char **argv) 
{
    if (argc) argc = 0;
    if (argv) argv = NULL;
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
        if (!world_map[(int)(player->x + player->dir_x * move)][(int)(player->y)])
        {
            player->x -= player->dir_x * move;
        }
        if (!world_map[(int)(player->x)][(int)(player->y + player->dir_y * move)])
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
    video_ptr->plane_y = 0.66f;
    video_ptr->font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 31, 63, 31);
}

void video_process(struct video *video_ptr, struct player *player_ptr)
{
    SDL_FillRect(video.screen, NULL, SDL_MapRGB(video.screen->format, 0, 0, 0));
    video_render_wall(video_ptr, player_ptr);
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
        video_vertical_line(video_ptr->screen, x, start, end, tex_x, side);
    }
}

void video_vertical_line(SDL_Surface *surface, int x, int start, int end, int tex_x, int side)
{
    for (int y = start; y < end; y++)
    {
        int height = end - start;
        int d = y * 256 - 240 * 128 + height * 128;
        int tex_y = ((d * 16) / height) / 256;
        int color = wall_sprite[tex_x][tex_y];
        int ncolor;
        if (side)
        {
            switch (color)
            {
            case 1:
                ncolor = video_24_to_16(35, 49, 70);
                break;
            case 2:
                ncolor = video_24_to_16(13, 27, 49);
                break;
            case 3:
                ncolor = video_24_to_16(5, 14, 29);
                break;
            }
        }
        else
        {
            switch (color)
            {
            case 1:
                ncolor = video_24_to_16(18, 25, 35);
                break;
            case 2:
                ncolor = video_24_to_16(7, 13, 25);
                break;
            case 3:
                ncolor = video_24_to_16(3, 7, 15);
                break;
            }
        }
        nSDL_SetPixel(surface, x, y, ncolor);
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
    y++;
}
