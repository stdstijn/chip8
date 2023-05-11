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
    PlatformCreate(&plat, "CHIP-8 Emulator", VIDEO_WIDTH, VIDEO_HEIGHT, scale);

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

void PlatformCreate(Platform* p, const char* title, int w, int h, int scale)
{
    SDL_Init(SDL_INIT_VIDEO);

    p->window = SDL_CreateWindow(title, 
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        w * scale, 
        h * scale, 
        0);

    p->renderer = SDL_CreateRenderer(p->window, 
        -1, 
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    p->texture = SDL_CreateTexture(p->renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STREAMING, 
        w, 
        h);
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

    static const uint8_t keyMap[] = {
        0x0, 0x1, 0x2, 0x3, 0x4, 0x5, 0x6, 0x7,
        0x8, 0x9, 0xA, 0xB, 0xC, 0xD, 0xE, 0xF
    };

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            quit = 1;
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE) 
                quit = 1;
            if (event.key.keysym.sym < 128) 
                keys[keyMap[event.key.keysym.sym]] = 1;
            break;
        case SDL_KEYUP:
            if (event.key.keysym.sym < 128) 
                keys[keyMap[event.key.keysym.sym]] = 0;
            break;
        }
    }

    return quit;
}
