#include "chip8/chip8.h"

#include <SDL2/SDL.h>

typedef struct Platform
{
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;
} Platform;

void PlatformCreate(Platform* p, const char* title, int windowW, int windowH, int textureW, int textureH);
void PlatformDestroy(Platform* p);
void PlatformUpdate(Platform* p, const void* buffer);
int PlatformProcessInput(uint8_t* keys);

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        SDL_Log("Usage: %s <ROM>\n", argv[0]);
        return 1;
    }

    int scale = 10;
    const char* romFilename = argv[1];

    SDL_RWops* fp = SDL_RWFromFile(romFilename, "rb");

    if (!fp)
    {
        SDL_Log("emulator could not open ROM: %s", romFilename);
        return 1;
    }

    Platform plat = { 0 };
    PlatformCreate(&plat, "CHIP-8 Emulator", VIDEO_WIDTH * scale, VIDEO_HEIGHT * scale, VIDEO_WIDTH, VIDEO_HEIGHT);

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
        quit = PlatformProcessInput(chip8.key);
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

void PlatformCreate(Platform* p, const char* title, int windowW, int windowH, int textureW, int textureH)
{
    SDL_Init(SDL_INIT_VIDEO);

    p->window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowW, windowH, 0);
    p->renderer = SDL_CreateRenderer(p->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    p->texture = SDL_CreateTexture(p->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, textureW, textureH);
}

void PlatformDestroy(Platform* p)
{
    SDL_DestroyTexture(p->texture);
    SDL_DestroyRenderer(p->renderer);
    SDL_DestroyWindow(p->window);
    SDL_Quit();
}

void PlatformUpdate(Platform* p, const void* buffer)
{
    SDL_SetRenderDrawColor(p->renderer, 0x00u, 0x00u, 0x00u, 0xFFu);
    SDL_RenderClear(p->renderer);

    static void* texture;
    static int pitch;

    SDL_LockTexture(p->texture, NULL, &texture, &pitch);

    const uint8_t* src = buffer;
    uint32_t* pixels = texture;

    for (size_t y = 0; y < VIDEO_HEIGHT; y++) 
    {
        for (size_t x = 0; x < VIDEO_WIDTH; x++) {

            int index = y * 64 + x;
            int bitIndex = index % 8;
            int byteIndex = index / 8;

            uint8_t bit = (src[byteIndex] >> bitIndex) & 0x01;
            uint8_t pixel = bit * 0xFFu;

            SDL_PixelFormat* format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA8888);
            uint32_t color = SDL_MapRGBA(format, pixel, pixel, pixel, 0xFFu);

            pixels[y * pitch / 4 + x] = color;
        }
    }

    SDL_UnlockTexture(p->texture);

    SDL_RenderCopy(p->renderer, p->texture, NULL, NULL);
    SDL_RenderPresent(p->renderer);
}

int PlatformProcessInput(uint8_t* keys)
{
    int quit = 0;

    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = 1;
                break;
            case SDLK_x:
                keys[0] = 1;
                break;
            case SDLK_1:
                keys[1] = 1;
                break;
            case SDLK_2:
                keys[2] = 1;
                break;
            case SDLK_3:
                keys[3] = 1;
                break;
            case SDLK_q:
                keys[4] = 1;
                break;
            case SDLK_w:
                keys[5] = 1;
                break;
            case SDLK_e:
                keys[6] = 1;
                break;
            case SDLK_a:
                keys[7] = 1;
                break;
            case SDLK_s:
                keys[8] = 1;
                break;
            case SDLK_d:
                keys[9] = 1;
                break;
            case SDLK_z:
                keys[0xA] = 1;
                break;
            case SDLK_c:
                keys[0xB] = 1;
                break;
            case SDLK_4:
                keys[0xC] = 1;
                break;
            case SDLK_r:
                keys[0xD] = 1;
                break;
            case SDLK_f:
                keys[0xE] = 1;
                break;
            case SDLK_v:
                keys[0xF] = 1;
                break;
            }
            break;
        case SDL_KEYUP:
            switch (event.key.keysym.sym)
            {
            case SDLK_x:
                keys[0] = 0;
                break;
            case SDLK_1:
                keys[1] = 0;
                break;
            case SDLK_2:
                keys[2] = 0;
                break;
            case SDLK_3:
                keys[3] = 0;
                break;
            case SDLK_q:
                keys[4] = 0;
                break;
            case SDLK_w:
                keys[5] = 0;
                break;
            case SDLK_e:
                keys[6] = 0;
                break;
            case SDLK_a:
                keys[7] = 0;
                break;
            case SDLK_s:
                keys[8] = 0;
                break;
            case SDLK_d:
                keys[9] = 0;
                break;
            case SDLK_z:
                keys[0xA] = 0;
                break;
            case SDLK_c:
                keys[0xB] = 0;
                break;
            case SDLK_4:
                keys[0xC] = 0;
                break;
            case SDLK_r:
                keys[0xD] = 0;
                break;
            case SDLK_f:
                keys[0xE] = 0;
                break;
            case SDLK_v:
                keys[0xF] = 0;
                break;
            }
            break;
        }
    }

    return quit;
}
