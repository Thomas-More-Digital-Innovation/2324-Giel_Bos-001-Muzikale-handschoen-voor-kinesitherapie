package fact.it.mvc.RewardMusic;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;

import fact.it.mvc.Note.NoteService;
import fact.it.mvc.RewardMusicList.RewardMusicList;
import fact.it.mvc.RewardMusicList.RewardMusicListService;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.ui.Model;
import fact.it.mvc.Note.Note;
import org.springframework.web.bind.annotation.RequestMapping;

@Controller
public class RewardMusicController {
    @Autowired
    private final NoteService noteService;
    private final RewardMusicService rewardMusicService;
    private final RewardMusicListService rewardMusicListService;

    public RewardMusicController(NoteService noteService, RewardMusicService rewardMusicService, RewardMusicListService rewardMusicListService){
        this.noteService = noteService;
        this.rewardMusicService = rewardMusicService;
        this.rewardMusicListService = rewardMusicListService;
    }

    @GetMapping("/manageMusic")
    public String manageMusic(Model model) {
        List<Note> notes = noteService.getAllNotes();
        List<RewardMusic> rewardMusics = rewardMusicService.getAllRewardMusic();
        List<RewardMusicList> rewardMusicLists = rewardMusicListService.getAllRewardMusicLists();

        model.addAttribute("notes", notes);
        model.addAttribute("rewardMusics", rewardMusics);
        model.addAttribute("rewardMusicLists", rewardMusicLists);
        return "manageRWMusic";
    }
    @RequestMapping("/addNote")
    public String requestMethodName(HttpServletRequest request, HttpServletResponse response) {
        String note = request.getParameter("note");
        int hzValue = Integer.parseInt(request.getParameter("hzValue"));
        Note newNote = new Note();
        newNote.setNote(note);
        newNote.setHzValue(hzValue);
        noteService.saveNote(newNote);

        return "redirect:/manageMusic";
    }
    @GetMapping("/addMusicList")
    public String addMusicNote(Model model) {
        List<Note> notes = noteService.getAllNotes();
        RewardMusic newRewardMusic = new RewardMusic();
        rewardMusicService.saveRewardMusic(newRewardMusic);
        List<RewardMusicList> rewardMusicLists = rewardMusicListService.getRewardMusicListsByRwMID(newRewardMusic.getRwMID());
        model.addAttribute("notes", notes);
        model.addAttribute("rewardMusic", newRewardMusic);
        model.addAttribute("rewardMusicLists", rewardMusicLists);
        return "manageRWMusicAdd";
    }
    @RequestMapping("/addNoteToList/{id}")
    public String addNoteToList(@PathVariable("id") int id, HttpServletRequest request, HttpServletResponse response, Model model) {
        int noteID = Integer.parseInt(request.getParameter("note"));
        List<RewardMusicList> rewardMusicLists = rewardMusicListService.getRewardMusicListsByRwMID(id);
        RewardMusicList newRewardMusicList = new RewardMusicList();
        newRewardMusicList.setNoteID(noteID);
        newRewardMusicList.setRwMID(id);
        newRewardMusicList.setPlace(rewardMusicLists.size()-1);
        rewardMusicListService.saveRewardMusicList(newRewardMusicList);

        RewardMusic rewardMusic = rewardMusicService.getRewardMusicById(id);
        List<Note> notes = noteService.getAllNotes();
        rewardMusicLists = rewardMusicListService.getRewardMusicListsByRwMID(id);
        model.addAttribute("notes", notes);
        model.addAttribute("rewardMusic", rewardMusic);
        model.addAttribute("rewardMusicLists", rewardMusicLists);
        return "manageRWMusicAdd";
    }
    @GetMapping("/editNoteToList/{id}")
    public String editNoteToList(@PathVariable("id") int id, Model model) {
        RewardMusic rewardMusic = rewardMusicService.getRewardMusicById(id);
        List<Note> notes = noteService.getAllNotes();
        List<RewardMusicList> rewardMusicLists = rewardMusicListService.getRewardMusicListsByRwMID(id);
        model.addAttribute("notes", notes);
        model.addAttribute("rewardMusic", rewardMusic);
        model.addAttribute("rewardMusicLists", rewardMusicLists);
        return "manageRWMusicAdd";
    }
    
    @GetMapping("/deleteMusic/{id}")
    public String deleteMusic(@PathVariable("id") int id) {
        rewardMusicService.deleteRewardMusicById(id);
        return "redirect:/manageMusic";
    }
    @GetMapping("/deleteMusicList/{id}")
    public String getMethodName(@PathVariable("id") int id) {
        int musicID = rewardMusicListService.getRewardMusicListById(id).getRwMID();
        rewardMusicListService.deleteRewardMusicListById(id);

        return "redirect:/editNoteToList/" + musicID;
    }
    
}
