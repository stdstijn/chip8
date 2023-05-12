#include "chip8/chip8.h"

#include <SDL2/SDL.h>

typedef struct Platform
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Platform;

void PlatformCreate(Platform* p, const char* title, int w, int h, int scale);
void PlatformDestroy(Platform* p);
void PlatformUpdate(Platform* p, const void* buffer);
int PlatformProcessInput(uint16_t* keys);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        SDL_Log("Usage: %s <ROM>\n", argv[0]);
        return 1;
    }

    const char* romFilename = argv[1];
    SDL_RWops* fp = SDL_RWFromFile(romFilename, "rb");

    if (!fp)
    {
        SDL_Log("emulator could not open ROM: %s", romFilename);
        return 1;
    }

    Platform plat = { 0 };
    PlatformCreate(&plat, "CHIP-8 Emulator", VIDEO_WIDTH, VIDEO_HEIGHT, 10);

    CPU chip8 = { 0 };
    Chip8_Create(&chip8);

    size_t memsize = MEMORY_SIZE - START_ADDRESS;
    SDL_RWread(fp, chip8.memory + START_ADDRESS, 1, memsize);
    SDL_RWclose(fp);

    int quit = 0;
    int time = 0;
    int lastPlatformUpdate = 0;

    while (!quit)
    {
        quit = PlatformProcessInput(&chip8.key);
        time = SDL_GetTicks();

        Chip8_Cycle(&chip8, time);

        if (time - lastPlatformUpdate >= 1000.0 / CLOCK_HZ + 0.5)
        {
            PlatformUpdate(&plat, chip8.gfx);

            lastPlatformUpdate = time;
        }
    }

    PlatformDestroy(&plat);

    return 0;
}

void PlatformCreate(Platform* p, const char* title, int w, int h, int scale)
{
    SDL_Init(SDL_INIT_VIDEO);

    p->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED, w * scale, h * scale, 0);

    p->renderer = SDL_CreateRenderer(p->window, -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    p->texture = SDL_CreateTexture(p->renderer, SDL_PIXELFORMAT_RGBA8888,
        SDL_TEXTUREACCESS_STREAMING, w, h);
}

void PlatformDestroy(Platform* p)
{
    SDL_DestroyTexture(p->texture);
    p->texture = NULL;

    SDL_DestroyRenderer(p->renderer);
    p->renderer = NULL;

    SDL_DestroyWindow(p->window);
    p->window = NULL;

    SDL_Quit();
}

void PlatformUpdate(Platform* p, const void* buffer)
{
    SDL_RenderClear(p->renderer);

    static void* texture;
    static int pitch;

    SDL_LockTexture(p->texture, NULL, &texture, &pitch);

    const uint8_t* src = buffer;
    uint32_t* pixels = texture;

    for (size_t y = 0; y < VIDEO_HEIGHT; y++)
    {
        for (size_t x = 0; x < VIDEO_WIDTH; x++)
        {
            int index = y * VIDEO_WIDTH + x;
            int bitIndex = index & 7u;
            int byteIndex = index >> 3u;

            uint8_t bit = (src[byteIndex] >> bitIndex) & 0x01u;
            uint8_t pixel = bit * 0xFFu;

            uint32_t color = (pixel) ? 0xFFFFFFFFu : 0x00000000u;

            pixels[y * pitch / 4 + x] = color;
        }
    }

    SDL_UnlockTexture(p->texture);

    SDL_RenderCopy(p->renderer, p->texture, NULL, NULL);
    SDL_RenderPresent(p->renderer);
}

int PlatformProcessInput(uint16_t* keys)
{
    int quit = 0;
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
        {
            int pressed = (event.type == SDL_KEYDOWN);

            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE: 
                quit = 1; 
                break;
            case SDLK_x:
                *keys = (*keys & ~(0x00000001u << 0x0u)) | (pressed << 0x0u);
                break;
            case SDLK_1:
                *keys = (*keys & ~(0x00000001u << 0x1u)) | (pressed << 0x1u);
                break;
            case SDLK_2:
                *keys = (*keys & ~(0x00000001u << 0x2u)) | (pressed << 0x2u);
                break;
            case SDLK_3:
                *keys = (*keys & ~(0x00000001u << 0x3u)) | (pressed << 0x3u);
                break;
            case SDLK_q:
                *keys = (*keys & ~(0x00000001u << 0x4u)) | (pressed << 0x4u);
                break;
            case SDLK_w:
                *keys = (*keys & ~(0x00000001u << 0x5u)) | (pressed << 0x5u);
                break;
            case SDLK_e:
                *keys = (*keys & ~(0x00000001u << 0x6u)) | (pressed << 0x6u);
                break;
            case SDLK_a:
                *keys = (*keys & ~(0x00000001u << 0x7u)) | (pressed << 0x7u);
                break;
            case SDLK_s:
                *keys = (*keys & ~(0x00000001u << 0x8u)) | (pressed << 0x8u);
                break;
            case SDLK_d:
                *keys = (*keys & ~(0x00000001u << 0x9u)) | (pressed << 0x9u);
                break;
            case SDLK_z:
                *keys = (*keys & ~(0x00000001u << 0xAu)) | (pressed << 0xAu);
                break;
            case SDLK_c:
                *keys = (*keys & ~(0x00000001u << 0xBu)) | (pressed << 0xBu);
                break;
            case SDLK_4:
                *keys = (*keys & ~(0x00000001u << 0xCu)) | (pressed << 0xCu);
                break;
            case SDLK_r:
                *keys = (*keys & ~(0x00000001u << 0xDu)) | (pressed << 0xDu);
                break;
            case SDLK_f:
                *keys = (*keys & ~(0x00000001u << 0xEu)) | (pressed << 0xEu);
                break;
            case SDLK_v:
                *keys = (*keys & ~(0x00000001u << 0xFu)) | (pressed << 0xFu);
                break;
            }
        }
        else if (event.type == SDL_QUIT)
        {
            quit = 1;
        }
    }

    return quit;
}
