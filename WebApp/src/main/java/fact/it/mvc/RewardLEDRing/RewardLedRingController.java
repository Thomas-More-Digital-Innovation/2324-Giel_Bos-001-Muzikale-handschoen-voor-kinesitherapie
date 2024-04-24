package fact.it.mvc.RewardLEDRing;

import java.util.List;

import javax.servlet.http.HttpServletRequest;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class RewardLedRingController {
    @Autowired
    private final RewardLEDRingService rewardLEDRingService;

    public RewardLedRingController(RewardLEDRingService rewardLEDRingService){
        this.rewardLEDRingService = rewardLEDRingService;
    }
    @GetMapping("/manageLED")
    public String manageLED(Model model) {
        List<RewardLEDRing> rewardLEDRings = rewardLEDRingService.getAllRewardLEDRings();
        model.addAttribute("rewardLEDRings", rewardLEDRings);
        return "manageRWLED";
    }
    @RequestMapping("/addLED")
    public String addLED(HttpServletRequest request) {
        RewardLEDRing newRewardLEDRing = new RewardLEDRing();
        String color0 = request.getParameter("color0");
        newRewardLEDRing.setHexCode0(color0);
        String color1 = request.getParameter("color1");
        newRewardLEDRing.setHexCode1(color1);
        String color2 = request.getParameter("color2");
        newRewardLEDRing.setHexCode2(color2);
        String color3 = request.getParameter("color3");
        newRewardLEDRing.setHexCode3(color3);
        String color4 = request.getParameter("color4");
        newRewardLEDRing.setHexCode4(color4);
        String color5 = request.getParameter("color5");
        newRewardLEDRing.setHexCode5(color5);
        String color6 = request.getParameter("color6");
        newRewardLEDRing.setHexCode6(color6);
        String color7 = request.getParameter("color7");
        newRewardLEDRing.setHexCode7(color7);
        String color8 = request.getParameter("color8");
        newRewardLEDRing.setHexCode8(color8);
        String color9 = request.getParameter("color9");
        newRewardLEDRing.setHexCode9(color9);
        String color10 = request.getParameter("color10");
        newRewardLEDRing.setHexCode10(color10);
        String color11 = request.getParameter("color11");
        newRewardLEDRing.setHexCode11(color11);

        rewardLEDRingService.saveRewardLEDRing(newRewardLEDRing);
        return "redirect:/manageLED";
    }
    @GetMapping("/deleteLED/{id}")
    public String deletePatient(@PathVariable("id") int id){
        rewardLEDRingService.deleteRewardLEDRingById(id);
        return "redirect:/manageLED";
    }
    @GetMapping("/editLED/{id}")
    public String editLED(@PathVariable("id") int id, Model model) {
        RewardLEDRing LEDRing = rewardLEDRingService.getRewardLEDRingById(id);
        List<String> hexCodes = rewardLEDRingService.getAllHexCodes(LEDRing);
        model.addAttribute("LEDRing", LEDRing);
        model.addAttribute("hexCodes", hexCodes);
        return "manageRWLEDEdit";
    }

    @RequestMapping("/updateLED/{id}")
    public String requestMethodName(@PathVariable("id") int id, HttpServletRequest request) {
        RewardLEDRing newRewardLEDRing = rewardLEDRingService.getRewardLEDRingById(id);
        String color0 = request.getParameter("color0");
        newRewardLEDRing.setHexCode0(color0);
        String color1 = request.getParameter("color1");
        newRewardLEDRing.setHexCode1(color1);
        String color2 = request.getParameter("color2");
        newRewardLEDRing.setHexCode2(color2);
        String color3 = request.getParameter("color3");
        newRewardLEDRing.setHexCode3(color3);
        String color4 = request.getParameter("color4");
        newRewardLEDRing.setHexCode4(color4);
        String color5 = request.getParameter("color5");
        newRewardLEDRing.setHexCode5(color5);
        String color6 = request.getParameter("color6");
        newRewardLEDRing.setHexCode6(color6);
        String color7 = request.getParameter("color7");
        newRewardLEDRing.setHexCode7(color7);
        String color8 = request.getParameter("color8");
        newRewardLEDRing.setHexCode8(color8);
        String color9 = request.getParameter("color9");
        newRewardLEDRing.setHexCode9(color9);
        String color10 = request.getParameter("color10");
        newRewardLEDRing.setHexCode10(color10);
        String color11 = request.getParameter("color11");
        newRewardLEDRing.setHexCode11(color11);

        rewardLEDRingService.saveRewardLEDRing(newRewardLEDRing);
        return "redirect:/manageLED";
    }
}