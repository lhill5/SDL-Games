import pygame
import os.path
import glob
from PIL import Image, ImageDraw
import shutil
from time import sleep


def main():
    ss_path = '/Users/landon/Documents/sdl_games/first_game/images'
    ss_name = 'main_character.png'

    images_dest = '/Users/landon/Documents/sdl_games/first_game/images/character_images'
    animations_dest = '/Users/landon/Documents/sdl_games/first_game/images/character_animations'

    load_in_spritesheet(ss_path, ss_name, images_dest, 0, 0, 832, 1344)
    load_in_spritesheet(ss_path, ss_name, animations_dest, 64, 1408, offset=128) 


def load_in_spritesheet(spritesheet_path, spritesheet_name, folder_destination, x_start, y_start, x_end=None, y_end=None, offset=0):

    image_path = os.path.join(spritesheet_path, spritesheet_name)

    spritesheet = Image.open(image_path)

    if (x_end is None):
        x_end = spritesheet.width
    if (y_end is None):
        y_end = spritesheet.height

    split_spritesheet_into_sprites(spritesheet, folder_destination, x_start, y_start, x_end, y_end, offset)


def split_spritesheet_into_sprites(spritesheet, dest, x_start, y_start, x_end, y_end, offset):
    # current_path = os.path.dirname(os.path.abspath(__file__))
    remove_files_from_directory(dest)
    crop_and_save_imgs(spritesheet, dest, x_start, y_start, x_end, y_end, offset)


def crop_and_save_imgs(spritesheet, dest, x_start, y_start, x_end, y_end, offset):

    find_last_char = lambda s, char : s.find(char)

    first_dir_index = dest[::-1].find('/')
    second_dir_index = dest[::-1].find('/', first_dir_index+1)

    folder_name = dest[-second_dir_index:]
    print(folder_name)
    subfolder_num = 0

    # subfolder_name = "folder" + str(subfolder_num)
    if 'character_images' in folder_name:
        subfolder_names = ["spellcast_back", "spellcast_left", "spellcast_front", "spellcast_right",
                       "stab_back", "stab_left", "stab_front", "stab_right",
                       "walk_back", "walk_left", "walk_front", "walk_right",
                       "slash_back", "slash_left", "slash_front", "slash_right",
                       "draw_bow_back", "draw_bow_left", "draw_bow_front", "draw_bow_right",
                       "die"]
    elif 'character_animations' in folder_name:
        subfolder_names = ["attack_back", "attack_left", "attack_front", "attack_right"]


    img_size = 64*64
    img_num = 1
    r, c = 1, 1
    for top in range(y_start, y_end, 64+(r*offset)):
        c = 1
        subfolder_name = subfolder_names[subfolder_num]
        subfolder_num += 1
        for left in range(x_start, x_end, 64+(c*offset)):

            cropped_image = spritesheet.crop((left, top, left+64, top+64))
            # if blank image (all black pixels) then no need to execute code below, continue through spritesheet
            if (get_black_pixel_count(cropped_image) == img_size):
                c += 1
                continue

            # left, upper, right, lower: tuple
            # cropped_image = spritesheet.crop((left, top, left+64, top+64))

            # goal is to dynamically figure out the correct dimension for different attack styles. 
            # Attacking left should include 64 pixels to the left, attack up and to the right changes size to include 64 pixels both up & right
            # Possibly change this in the future to only include necessary pixels to fit image, instead of just expanding window by 64 pixels
            
            # this could be useful for detecting hit box with enemy hit box when attacking, if I expanded width and height (can move x-y direction)
            # to static 128 pixels, then hit box wouldn't be accurate, should only change from 64x64 to 128x64 when attacking

            if folder_name == "character_animations":
                shift_left = spritesheet.crop((left-64, top, left, top+64))
                shift_right = spritesheet.crop((left+64, top, left+128, top+64))
                shift_up = spritesheet.crop((left, top-64, left+64, top))
                shift_down = spritesheet.crop((left, top+64, left+64, top+128))
                shift_right_down = spritesheet.crop((left, top+64, left+128, top+128))
                
                # image 17 needs to include right and down pixels, need better algorithm than this,
                # I should create something that analizes square around image to include column/row of pixels if not black pixels, 
                # row by row and col by col

                # average_pixel_color = get_average_pixel_color(cropped_image)

                # cropped_image.show("cropped image")
                # shift_left.show("cropped image left")
                # cropped_image_right.show("cropped_image_right")
                # cropped_image_top.show("cropped_image_top")
                # cropped_image_bottom.show("cropped_image_bottom")
                # print(img_num, left, 64+(c*offset), average_pixel_color)


                # check if shifting image left reveals any cropped part of the image, if # black pixels = 4096, then no crop issue
                # otherwise, that means the original image has more pixels to the left and we should include that in final result
                l, u, r, d = left, top, left+64, top+64
                expanded_hitBox = False
                if (get_black_pixel_count(shift_left) != img_size):
                    l -= 64
                    expanded_hitBox = True
                if (get_black_pixel_count(shift_right) != img_size):
                    r += 64
                    expanded_hitBox = True
                if (get_black_pixel_count(shift_up) != img_size):
                    u -= 64
                    expanded_hitBox = True
                if (get_black_pixel_count(shift_down) != img_size):
                    d += 64
                    expanded_hitBox = True

                if (expanded_hitBox):
                    cropped_image = spritesheet.crop((l, u, r, d))

                # if (img_num == 17):
                #     # shift_left.show()
                #     # shift_right.show()
                #     # shift_up.show()
                #     shift_down.show()
                #     shift_right_down.show()
                    
                #     cropped_image.show()
                #     print('here')
                #     print(l, u, r, d)     
                #     print()     
                # it's possible that all 4 sides, left/right/up/down all have img_size black pixels, no crop issues
                # therefore leaving cropped_image as it is

                # if img_num == 4:
                #     print('image: ' + str(img_num) + " cropped image: ", get_black_pixel_count(cropped_image))
                #     print('image: ' + str(img_num) + " cropped image left: ", get_black_pixel_count(shift_left))
                #     print('image: ' + str(img_num) + " cropped image right: ", get_black_pixel_count(shift_right))
                #     print('image: ' + str(img_num) + " cropped image top: ", get_black_pixel_count(shift_up))
                #     print('image: ' + str(img_num) + " cropped image bottom: ", get_black_pixel_count(shift_down))

                # print (average_pixel_color)
                # pixels in image are RGBA format

            # save image to output folder
            img_num_str = str(img_num).zfill(3)
            img_name = 'image_' + img_num_str
            img_num += 1

            folder_path = os.path.join(folder_name, subfolder_name)
            if not os.path.isdir(folder_path):
                make_dir(folder_path)

            img_path = os.path.join(folder_path, img_name + '.png')
            cropped_image.save(img_path, format="PNG")
            # cropped_image.show()
            c += 1
        r += 1


def get_black_pixel_count(img):
    img_resized = img.resize((64,64))
    black_count, count = 0, 0
    for pixel in img_resized.getdata():
        if pixel == (0,0,0,0):
            black_count += 1
        count += 1
    return black_count


def get_average_pixel_color(img):
    img2 = img.resize((1, 1))
    color = img2.getpixel((0, 0))
    # print('#{:02x}{:02x}{:02x}'.format(*color))
    return color


def remove_files_from_directory(dir_name):
    files = glob.glob(dir_name)
    for f in files:
        shutil.rmtree(f)
    os.mkdir(dir_name)


def make_dir(dir_path):
    print(dir_path)
    try:
        os.mkdir(dir_path)
    except OSError:
        print('failed to create directory, exiting program')
        exit(1)


if __name__ == '__main__':
    main()
