import random


class Generator:
    gen_name = "Abstract Generator"

    def next_byte(self):
        curent_id = 0
        res = 0
        
        while curent_id < 8:
            generated_v = self.next()

            for b in generated_v:
                res = res | (b << curent_id);
                
                curent_id += 1;

        return res

    def next(self):
        pass

    def about(self):
        return "Generator: " + self.gen_name


class BuildInGenerator(Generator):
    def __init__(self):
        self.gen_name = "BuildInGenerator";

    def next(self):
        return [random.getrandbits(1)]