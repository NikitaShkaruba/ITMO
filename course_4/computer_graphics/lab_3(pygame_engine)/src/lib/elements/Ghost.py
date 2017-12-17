from src.lib.elements.Player import Player


class Ghost(Player):
    # Change the speed of the ghost
    def change_speed(self, turn_list, ghost, turn, steps, l):
        try:
            z = turn_list[turn][2]
            if steps < z:
                self.change_x = turn_list[turn][0]
                self.change_y = turn_list[turn][1]
                steps += 1
            else:
                if turn < l:
                    turn += 1
                elif ghost == "clyde":
                    turn = 2
                else:
                    turn = 0
                self.change_x = turn_list[turn][0]
                self.change_y = turn_list[turn][1]
                steps = 0
            return [turn, steps]
        except IndexError:
            return [0, 0]