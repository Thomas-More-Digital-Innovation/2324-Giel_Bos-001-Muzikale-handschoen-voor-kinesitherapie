package fact.it.examplemvc.controller;

import fact.it.examplemvc.model.Dish;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.servlet.http.HttpServletRequest;
import java.util.ArrayList;

@Controller
public class MainController {

    @RequestMapping("/aboutus")
    public String aboutus() {
        return "aboutus";
    }

    @RequestMapping("/singledish")
    public String singledish(Model model) {

        Dish dish = new Dish("Pizza calzone", 964, true);
        model.addAttribute("dish",dish);

        return "dishdetails";
    }

    @RequestMapping("/dishlist")
    public String dishlist(Model model) {

        ArrayList<Dish> dishList = new ArrayList<>();
        dishList.add(new Dish("Pizza calzone", 964, true));
        dishList.add(new Dish("Caesar Salad with Chicken", 260, false));
        dishList.add(new Dish("Apple Lattice Pie", 360, true));

        model.addAttribute("dishList",dishList);

        return "dishlist";
    }

    @RequestMapping("/newdish")
    public String newdish() {
        return "newdish";
    }

    @RequestMapping("/submitnewdish")
    public String submitnewdish(HttpServletRequest request, Model model) {

        String name = request.getParameter("name");
        Integer calories = Integer.parseInt(request.getParameter("calories"));
        boolean vegetarian = (request.getParameter("vegetarian") != null);

        Dish dish = new Dish(name, calories, vegetarian);
        model.addAttribute("dish",dish);

        return "dishdetails";
    }

}
