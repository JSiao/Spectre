#include <os.h>
#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <math.h>

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

static struct player
{
    double x,y;
    double dir_x, dir_y;
} player = {11, 11, -1, 0};

static struct game
{
    double time_0, time_1;
    char running;
} game_data = {0, 0, 1};

struct video
{
    SDL_Surface *screen;
    double plane_x, plane_y;
} video;

void key_process(struct game *, struct player*, struct video *);

void video_init(struct video *);
void video_process(struct video *, struct player *);
void video_render_wall(struct video *, struct player *);
void video_vertical_line(SDL_Surface *, int, int, int, int);

void debug_render(struct video *, nSDL_Font *);

int main(int argc, char **argv) 
{
    if (argc) argc = 0;
    if (argv) argv = NULL;
    nSDL_Font *font;
    video_init(&video);
    font = nSDL_LoadFont(NSDL_FONT_TINYTYPE, 255, 255, 255);
    SDL_FillRect(video.screen, NULL, SDL_MapRGB(video.screen->format, 0, 0, 0));
    nSDL_DrawString(video.screen, font, 10, 10, "Justin was Here. \x1");
    while(game_data.running)
    {
        key_process(&game_data, &player, &video);
        debug_render(&video, font);
        video_process(&video, &player);
        sleep(10);
    }
    SDL_Quit();
    return 0;
}

void key_process(struct game *data, struct player *player, struct video *video)
{
    const double rotation = 0.3;
    const double move     = 0.5;
    if (isKeyPressed(KEY_NSPIRE_ESC))
    {
        data->running = 0;
    }
    if (isKeyPressed(KEY_NSPIRE_UP))
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
    if (isKeyPressed(KEY_NSPIRE_DOWN))
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
    if (isKeyPressed(KEY_NSPIRE_RIGHT))
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
    if (isKeyPressed(KEY_NSPIRE_LEFT))
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
}

void video_process(struct video *video_ptr, struct player *player_ptr)
{
    SDL_FillRect(video.screen, NULL, SDL_MapRGB(video.screen->format, 0, 0, 0));
    video_render_wall(video_ptr, player_ptr);
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
        if (side == 0) distance = (map_x - player_ptr->x + (1 - step_x) / 2) / ray_x;
        else           distance = (map_y - player_ptr->y + (1 - step_y) / 2) / ray_y;
        int line_height = (int)(240 / distance);
        int start       = (-line_height / 2) + 120;
        if (start < 0) start = 0;
        int end         = (line_height / 2) + 120;
        if (end >= 240) end = 239;
        int color       = 0x000007E;
        if (side) color = 0x000001F;
        video_vertical_line(video_ptr->screen, x, start, end, color);
    }
}

void video_vertical_line(SDL_Surface *surface, int x, int start, int end, int color)
{
    for (int y = start; y <= end; y++)
    {
        nSDL_SetPixel(surface, x, y, color);
    }
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
