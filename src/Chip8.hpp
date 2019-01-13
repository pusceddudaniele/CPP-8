#pragma once
#include <memory>
#include <random>
#include <cstdint>
#include <string>

class Chip8{
    public:
        //This method attempts copying the contents of
        //a file to chip8's RAM, starting at addr 0x200
        //The file might be too big to fit in the RAM,
        //or we might be unable to open it
        Chip8(std::string romFilename);

        //Execute the instruction pointed by the program counter
        void step();

        //Returns false when Chip8 has finished execution
        bool isRunning();

        //Input and output is up to subclasses to implement
        virtual void handleInput() = 0;
        virtual void display() = 0;

        //Virtual destructor
        virtual ~Chip8();

    protected:
        //These will be used by child classes for input and output
        bool running;
        bool screenUpdated = false;
        std::array<bool, 64*32> screen;
        std::array<bool, 16> keys;

    private:
    //VARIABLES
        //16 general purpose 8-bit registers
        //Referred to as Vx, where x is a hex digit.
        //VF is a Flag register used by some instructions
        std::uint8_t V[16];

        //Stack
        std::uint16_t stack[16];

        //Stack Pointer
        //Points to topmost level of the stack
        std::uint8_t SP = 0;

        //4KB of RAM.
        //Chip-8 programs should start at 0x200 (512)
        std::array<std::uint8_t, 4096> mem;

        //Program Counter
        //Used to store the currently executing address
        std::uint16_t PC = 0x200;

        //This register is usually used to store addresses
        std::uint16_t I = 0;

        //Delay and Sound timers
        //When they are non-zero, they are decremented at a rate of 60hz
        std::uint8_t delayTimer = 0;
        std::uint8_t soundtimer = 0;

        //Utilities for random number generation
        std::default_random_engine randEng;
        std::uniform_int_distribution<std::uint8_t> intDist{0, 255};


    //METHODS
        //Helper method for draw instruction
        //Returns true if collifion happened
        bool drawSprite(int x, int y, std::uint16_t addr, std::size_t len);

        //Helper method for XNNN instructions
        std::uint16_t getNNN(std::uint8_t high, std::uint8_t low);

        //Report an unknown opcode
        void reportCode(std::uint8_t high, std::uint8_t low);

    //CONSTANTS
        //This is a group of sprites representing the hex digits
        //They will be stored in RAM 0x000 to 0x1FF
        //Each sprite is 5 bytes long
        //This array is not pretty but I don't see
        //other ways to do this.
        static constexpr std::array<std::uint8_t, 16*5> hexSprites =
            {
                //0
                0b11110000,
                0b10010000,
                0b10010000,
                0b10010000,
                0b11110000,

                //1
                0b00100000,
                0b01100000,
                0b00100000,
                0b00100000,
                0b01110000,

                //2
                0b11110000,
                0b00010000,
                0b11110000,
                0b10000000,
                0b11110000,

                //3
                0b11110000,
                0b00010000,
                0b11110000,
                0b00010000,
                0b11110000,

                //4
                0b10010000,
                0b10010000,
                0b11110000,
                0b00010000,
                0b00010000,

                //5
                0b11110000,
                0b10000000,
                0b11110000,
                0b00010000,
                0b11110000,

                //6
                0b11110000,
                0b10000000,
                0b11110000,
                0b10010000,
                0b11110000,

                //7
                0b11110000,
                0b00010000,
                0b00100000,
                0b01000000,
                0b01000000,

                //8
                0b11110000,
                0b10010000,
                0b11110000,
                0b10010000,
                0b11110000,

                //9
                0b11110000,
                0b10010000,
                0b11110000,
                0b00010000,
                0b11110000,

                //A
                0b11110000,
                0b10010000,
                0b11110000,
                0b10010000,
                0b10010000,

                //B
                0b11100000,
                0b10010000,
                0b11100000,
                0b10010000,
                0b11100000,

                //C
                0b11110000,
                0b10000000,
                0b10000000,
                0b10000000,
                0b11110000,

                //D
                0b11100000,
                0b10010000,
                0b10010000,
                0b10010000,
                0b11100000,

                //E
                0b11110000,
                0b10000000,
                0b11110000,
                0b10000000,
                0b11110000,

                //F
                0b11110000,
                0b10000000,
                0b11110000,
                0b10000000,
                0b10000000,
             };
};