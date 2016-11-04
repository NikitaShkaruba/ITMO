package itmo.dbs.controllers;

import org.springframework.web.bind.annotation.*;

// Just a custom controller we can use in the near future
@RestController
public class GreetingController {
    @ResponseBody
    @RequestMapping("/greeting")
    public String greeting(@RequestParam(value="name", defaultValue="World") String name) {
        return "Hello, " + name + "!";
    }
}
