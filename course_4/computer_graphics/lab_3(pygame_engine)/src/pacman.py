import pygame
from src.lib.constants.colors import black, white, red, yellow
from src.lib.constants.ghost_directions import pinky_directions, blinky_directions, inky_directions, clyde_directions, \
    pinky_directions_length, blinky_directions_length, inky_directions_length, clyde_directions_length
from src.lib.elements.Block import Block
from src.lib.elements.Player import Player
from src.lib.elements.Ghost import Ghost
from src.lib.helpers.initialize import initialize_map, initialize_gate

pacman_icon = pygame.image.load('resources/images/pacman.png')
pygame.display.set_icon(pacman_icon)

pygame.mixer.init()
pygame.mixer.music.load('resources/music/pacman.mp3')
pygame.mixer.music.play(-1, 0.0)

screen = pygame.display.set_mode([606, 606])
pygame.display.set_caption('Pacman')

background = pygame.Surface(screen.get_size())                  # Create a surface we can draw on
background = background.convert()                               # Used for converting color maps and such
background.fill(black)                                          # Fill the screen with a black background

clock = pygame.time.Clock()

pygame.font.init()
font = pygame.font.Font("resources/fonts/freesansbold.ttf", 24)

# default locations for Pacman and ghosts
width = 303 - 16
pacman_height = (7 * 60) + 19
ghost_height = (4 * 60) + 19
blinky_height = (3 * 60) + 19
inky_width = 303 - 16 - 32
clyde_width = 303 + (32 - 16)


# Game main function
def start_game():
    all_sprites_list = pygame.sprite.RenderPlain()
    block_list = pygame.sprite.RenderPlain()
    ghost_list = pygame.sprite.RenderPlain()
    pacman_collide = pygame.sprite.RenderPlain()

    wall_list = initialize_map(all_sprites_list)
    gate = initialize_gate(all_sprites_list)

    p_turn = 0
    p_steps = 0

    b_turn = 0
    b_steps = 0

    i_turn = 0
    i_steps = 0

    c_turn = 0
    c_steps = 0

    # Create the player paddle object
    pacman = Player(width, pacman_height, "resources/images/pacman.png")
    all_sprites_list.add(pacman)
    pacman_collide.add(pacman)

    blinky = Ghost(width, blinky_height, "resources/images/Blinky.png")
    ghost_list.add(blinky)
    all_sprites_list.add(blinky)

    pinky = Ghost(width, ghost_height, "resources/images/Pinky.png")
    ghost_list.add(pinky)
    all_sprites_list.add(pinky)

    inky = Ghost(inky_width, ghost_height, "resources/images/Inky.png")
    ghost_list.add(inky)
    all_sprites_list.add(inky)

    clyde = Ghost(clyde_width, ghost_height, "resources/images/Clyde.png")
    ghost_list.add(clyde)
    all_sprites_list.add(clyde)

    # Draw the grid
    for row in range(19):
        for column in range(19):
            if (row == 7 or row == 8) and (column == 8 or column == 9 or column == 10):
                continue
            else:
                block = Block(yellow, 4, 4)

                # Set a random location for the block
                block.rect.x = (30 * column + 6) + 26
                block.rect.y = (30 * row + 6) + 26

                b_collide = pygame.sprite.spritecollide(block, wall_list, False)
                p_collide = pygame.sprite.spritecollide(block, pacman_collide, False)
                if b_collide:
                    continue
                elif p_collide:
                    continue
                else:
                    # Add the block to the list of objects
                    block_list.add(block)
                    all_sprites_list.add(block)

    block_list_length = len(block_list)
    score = 0
    done = False

    while not done:
        # Process events
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                done = True

            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    pacman.change_speed(-30, 0)
                if event.key == pygame.K_RIGHT:
                    pacman.change_speed(30, 0)
                if event.key == pygame.K_UP:
                    pacman.change_speed(0, -30)
                if event.key == pygame.K_DOWN:
                    pacman.change_speed(0, 30)

            if event.type == pygame.KEYUP:
                if event.key == pygame.K_LEFT:
                    pacman.change_speed(30, 0)
                if event.key == pygame.K_RIGHT:
                    pacman.change_speed(-30, 0)
                if event.key == pygame.K_UP:
                    pacman.change_speed(0, 30)
                if event.key == pygame.K_DOWN:
                    pacman.change_speed(0, -30)

        # Process tick
        pacman.update(wall_list, gate)

        # Update ghosts
        turn_steps = pinky.change_speed(pinky_directions, False, p_turn, p_steps, pinky_directions_length)
        p_turn = turn_steps[0]
        p_steps = turn_steps[1]
        pinky.change_speed(pinky_directions, False, p_turn, p_steps, pinky_directions_length)
        pinky.update(wall_list, False)

        turn_steps = blinky.change_speed(blinky_directions, False, b_turn, b_steps, blinky_directions_length)
        b_turn = turn_steps[0]
        b_steps = turn_steps[1]
        blinky.change_speed(blinky_directions, False, b_turn, b_steps, blinky_directions_length)
        blinky.update(wall_list, False)

        turn_steps = inky.change_speed(inky_directions, False, i_turn, i_steps, inky_directions_length)
        i_turn = turn_steps[0]
        i_steps = turn_steps[1]
        inky.change_speed(inky_directions, False, i_turn, i_steps, inky_directions_length)
        inky.update(wall_list, False)

        turn_steps = clyde.change_speed(clyde_directions, "clyde", c_turn, c_steps, clyde_directions_length)
        c_turn = turn_steps[0]
        c_steps = turn_steps[1]
        clyde.change_speed(clyde_directions, "clyde", c_turn, c_steps, clyde_directions_length)
        clyde.update(wall_list, False)

        # See if the Pacman block has collided with anything.
        blocks_hit_list = pygame.sprite.spritecollide(pacman, block_list, True)

        # Check the list of collisions.
        if len(blocks_hit_list) > 0:
            score += len(blocks_hit_list)

        # Draw world
        screen.fill(black)

        wall_list.draw(screen)
        gate.draw(screen)
        all_sprites_list.draw(screen)
        ghost_list.draw(screen)

        text = font.render("Score: " + str(score) + "/" + str(block_list_length), True, red)
        screen.blit(text, [10, 10])

        # Check if won
        if score == block_list_length:
            draw_end_screen("Congratulations, you won!", 145, all_sprites_list, block_list, ghost_list, pacman_collide,
                            wall_list, gate)

        # Check if lose
        ghost_hit_list = pygame.sprite.spritecollide(pacman, ghost_list, False)
        if ghost_hit_list:
            draw_end_screen("Game Over", 235, all_sprites_list, block_list, ghost_list, pacman_collide, wall_list, gate)

        pygame.display.flip()
        clock.tick(10)


def draw_end_screen(message, left, all_sprites_list, block_list, ghosts_list, pacman_collide, wall_list, gate):
    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_ESCAPE:
                    pygame.quit()
                if event.key == pygame.K_RETURN:
                    del all_sprites_list
                    del block_list
                    del ghosts_list
                    del pacman_collide
                    del wall_list
                    del gate
                    start_game()

        surface = pygame.Surface((400, 200))  # the size of your rect
        surface.set_alpha(10)  # alpha level
        surface.fill((128, 128, 128))  # this fills the entire surface
        screen.blit(surface, (100, 200))  # (0,0) are the top-left coordinates

        text1 = font.render(message, True, white)
        screen.blit(text1, [left, 233])

        text2 = font.render("To play again, press ENTER.", True, white)
        screen.blit(text2, [135, 303])
        text3 = font.render("To quit, press ESCAPE.", True, white)
        screen.blit(text3, [165, 333])

        pygame.display.flip()
        clock.tick(10)


pygame.init()
start_game()
pygame.quit()
