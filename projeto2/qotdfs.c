/*
  FUSE: Filesystem in Userspace
  Copyright (C) 2001-2007  Miklos Szeredi <miklos@szeredi.hu>

  This program can be distributed under the terms of the GNU GPL.
  See the file COPYING.

  gcc -Wall hello.c `pkg-config fuse --cflags --libs` -o hello
*/

#define FUSE_USE_VERSION 26

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#define QN 347

struct tm current_time;

const char *const quotes[QN] = {
        "Don't worry about what anybody else is going to do. The best way to\npredict the future is to invent it.\n-- Alan Kay",
        "Premature optimization is the root of all evil (or at least most of it)\nin programming.\n-- Donald Knuth",
        "Lisp has jokingly been called \"the most intelligent way to misuse a\ncomputer\". I think that description is a great compliment because it\ntransmits the full flavor of liberation: it has assisted a number of our\nmost gifted fellow humans in thinking previously impossible thoughts.\n-- Edsger Dijkstra, CACM, 15:10",
        "Keep away from people who try to belittle your ambitions. Small people\nalways do that, but the really great make you feel that you, too, can\nbecome great.\n-- Mark Twain",
        "What Paul does, and does very well, is to take ideas and concepts that\nare beautiful in the abstract, and brings them down to a real world\nlevel. That's a rare talent to find in writing these days.\n-- Jeff \"hemos\" Bates, Director, OSDN; Co-evolver, Slashdot",
        "Since programmers create programs out of nothing, imagination is our\nonly limitation. Thus, in the world of programming, the hero is the one\nwho has great vision. Paul Graham is one of our contemporary heroes. He\nhas the ability to embrace the vision, and to express it plainly. His\nworks are my favorites, especially the ones describing language design.\nHe explains secrets of programming, languages, and human nature that can\nonly be learned from the hacker experience. This book shows you his\ngreat vision, and tells you the truth about the nature of hacking.\n-- Yukihiro \"Matz\" Matsumoto, creator of Ruby",
        "To follow the path:\n    look to the master,\n    follow the master,\n    walk with the master,\n    see through the master,\n    become the master.\n-- Modern zen Poem",
        "No problem should ever have to be solved twice.\n-- Eric S. Raymond, How to become a hacker",
        "Attitude is no substitute for competence.\n-- Eric S. Raymond, How to become a hacker",
        "It is said that the real winner is the one who lives in today but able\nto see tomorrow.\n-- Juan Meng, Reviewing \"The future of ideas\" by Lawrence Lessig",
        "Fools ignore complexity. Pragmatists suffer it. Some can avoid it.\nGeniuses remove it.\n-- Alan J. Perlis (Epigrams in programming)",
        "A year spent in artificial intelligence is enough to make one believe in\nGod.\n-- Alan J. Perlis (Epigrams in programming)",
        "Dealing with failure is easy: Work hard to improve. Success is also easy\nto handle: You've solved the wrong problem. Work hard to improve.\n-- Alan J. Perlis (Epigrams in programmi ng)",
        "Within a computer natural language is unnatural.\n-- Alan J. Perlis (Epigrams in programming)",
        "You think you know when you learn, are more sure when you can write,\neven more when you can teach, but certain when you can program.\n-- Alan J. Perlis (Epigrams in programming)",
        "Adapting old programs to fit new machines usually means adapting new\nmachines to behave like old ones.\n-- Alan J. Perlis (Epigrams in programming)",
        "A little learning is a dangerous thing.\n-- Alexander Pope",
        "Computer science education cannot make anybody an expert programmer any\nmore than studying brushes and pigment can make somebody an expert\npainter.\n-- Eric Raymond",
        "Einstein argued that there must be simplified explanations of nature,\nbecause God is not capricious or arbitrary.\n-- Frederick P. Brooks, No Sliver Bullet.",
        "Students should be evaluated on how well they can achieve the goals they\nstrived to achieve within a realistic context. Students need to learn to\ndo things, not know things.\n-- Roger Schank, Engines for Education",
        "We remember what we learn when we care about performing better and when\nwe believe that what we have been asked to do is representative of\nreality.\n-- Roger Schank, Engines for Education",
        "There really is no learning without doing.\n-- Roger Schank, Engines for Education",
        "We really have to get over the idea that some stuff is just worth\nknowing even if you never do anything with it. Human memories happily\nerase stuff that has no purpose, so why try to fill up children's heads\nwith such stuff?\n-- Roger Schank, Engines for Education",
        "La tactique, c'est ce que vous faites quand il y a quelque chose à\nfaire; la stratégie, c'est ce que vous faites quand il n'y a rien à\nfaire.\n-- Xavier Tartacover",
        "The only problems we can really solve in a satisfactory manner are those\nthat finally admit a nicely factored solution.\n-- E. W. Dijkstra, The humble programmer",
        "The best way to learn to live with our limitations is to know them.\n--E. W. Dijkstra, The humble programmer",
        "This challenge, viz. the confrontation with the programming task, is so\nunique that this novel experience can teach us a lot about ourselves. It\nshould deepen our understanding of the processes of design and creation,\nit should give us better control over the task of organizing our\nthoughts. If it did not do so, to my taste we should no deserve the\ncomputer at all!  It has allready taught us a few lessons, and the one I\nhave chosen to stress in this talk is the following. We shall do a much\nbetter programming job, provided that we approach the task with a full\nappreciation of its tremenduous difficulty, provided that we stick to\nmodest and elegant programming languages, provided that we respect the\nintrinsec limitations of the human mind and approach the task as Very\nHumble Programmers.\n-- E. W. Dijkstra, The humble programmer",
        "Ce n'est que par les relations qu'on entretient entre nos différentes\nconnaissances qu'elles nous restent accessibles.\n-- Shnuup, sur l'hypertexte (SELFHTML -> Introduction -> Definitions sur l'hypertexte)",
        "We now come to the decisive step of mathematical abstraction: we forget\nabout what the symbols stand for. ...[The mathematician] need not be\nidle; there are many operations which he may carry out with these\nsymbols, without ever having to look at the things they stand for.\n-- Hermann Weyl, The Mathematical Way of Thinking",
        "An expert is, according to my working definition \"someone who doesn't\nneed to look up answers to easy questions\".\n-- Eric Lippert.",
        "The programmer must seek both perfection of part and adequacy of\ncollection.\n-- Alan J. Perlis",
        "Thus, programs must be written for people to read, and only incidentally\nfor machines to execute.\n-- Alan J. Perlis",
        "We control complexity by building abstractions that hide details when\nappropriate. We control complexity by establishing conventional\ninterfaces that enable us to construct systems by combining standard,\nwell-understood pieces in a ``mix and match'' way. We control complexity\nby establishing new languages for describing a design, each of which\nemphasizes particular aspects of the design and deemphasizes others.\n-- Alan J. Perlis",
        "The acts of the mind, wherein it exerts its power over simple ideas, are\nchiefly these three: 1. Combining several simple ideas into one compound\none, and thus all complex ideas are made. 2. The second is bringing two\nideas, whether simple or complex, together, and setting them by one\nanother so as to take a view of them at once, without uniting them into\none, by which it gets all its ideas of relations. 3. The third is\nseparating them from all other ideas that accompany them in their real\nexistence: this is called abstraction, and thus all its general ideas\nare made.\n-- John Locke, An Essay Concerning Human Understanding (1690)",
        "Lisp programmers know the value of everything but the cost of nothing.\n-- Alan J. Perlis",
        "An interpreter raises the machine to the level of the user program; a\ncompiler lowers the user program to the level of the machine language.\n-- SICP",
        "Everything should be made as simple as possible, but no simpler.\n-- Albert Einstein",
        "The great dividing line between success and failure can be expressed in\nfive words: \"I did not have time.\"\n-- WestHost weekly newsletter 14 Feb 2003",
        "When your enemy is making a very serious mistake, don't be impolite and\ndisturb him.\n-- Napoleon Bonaparte (allegedly)",
        "A charlatan makes obscure what is clear; a thinker makes clear what is\nobscure.\n-- Hugh Kingsmill",
        "There are two ways of constructing a software design; one way is to make\nit so simple that there are obviously no deficiencies, and the other way\nis to make it so complicated that there are no obvious deficiencies. The\nfirst method is far more difficult.\n-- C. A. R. Hoare",
        "And if you go too far up, abstraction-wise, you run out of oxygen.\nSometimes smart thinkers just don't know when to stop, and they create\nthese absurd, all-encompassing, high-level pictures of the universe that\nare all good and fine, but don't actually mean anything at all.\n-- Joel Spolsky		",
        "The three chief virtues of a programmer are: Laziness, Impatience and\nHubris.\n-- Larry Wall (Programming Perl)",
        "All non-trivial abstractions, to some degree, are leaky.\n-- Joel Spolsky (The Law of Leaky Abstractions)",
        "XML wasn't designed to be edited by humans on a regular basis.\n-- Guido van Rossum",
        "Premature abstraction is an equally grevious sin as premature\noptimization.\n-- Keith Devens",
        "You can have premature generalization as well as premature optimization.\n-- Bjarne Stroustrup",
        "He causes his sun to rise on the evil and the good, and sends rain on\nthe righteous and the unrighteous.\n-- Matthew 5:45",
        "A language that doesn't affect the way you think about programming, is\nnot worth knowing.\n-- Alan Perlis",
        "Je n'ai fait celle-ci plus longue que parce que je n'ai pas eu le loisir\nde la faire plus courte. (I have made this letter so long only because I\ndid not have the leisure to make it shorter.)\n-- Blaise Pascal (Lettres Provinciales)",
        "Men never do evil so completely and cheerfully as when they do it from\nreligious conviction.\n-- Blaise Pascal (attributed)",
        "Everybody makes their own fun. If you don't make it yourself, it ain't\nfun -- it's entertainment.\n-- David Mamet (as relayed by Joss Whedon)",
        "If we wish to count lines of code, we should not regard them as *lines\nproduced* but as *lines spent*.\n-- Edsger Dijkstra		",
        "Sometimes a man with too broad a perspective reveals himself as having\nno real perspective at all. A man who tries too hard to see every side\nmay be a man who is trying to avoid choosing any side. A man who tries\ntoo hard to seek a deeper truth may be trying to hide from the truth he\nalready knows.  That is not a sign of intellectual sophistication and\n\"great thinking\". It is a demonstration of moral degeneracy and\ncowardice.\n-- Steven Den Beste",
        "Omit needless words.\n-- William Strunk, Jr. (The Elements of Style)",
        "I have never met a man so ignorant that I couldn't learn something from\nhim.\n-- Galileo Galilei",
        "A society that puts equality -- in the sense of equality of outcome --\nahead of freedom will end up with neither equality nor freedom. The use\nof force to achieve equality will destroy freedom, and the force,\nintroduced for good purposes, will end up in the hands of people who use\nit to promote their own interests.\n-- Milton Friedman (Thomas Sowell: A Conflict of Visions, p130)",
        "Philosophy: the finding of bad reasons for what one believes by\ninstinct.\n-- Brave New World (paraphrased)",
        "Of all tyrannies a tyranny sincerely exercised for the good of its\nvictims may be the most oppressive. It may be better to live under\nrobber barons than under omnipotent moral busybodies, The robber baron's\ncruelty may sometimes sleep, his cupidity may at some point be satiated;\nbut those who torment us for own good will torment us without end, for\nthey do so with the approval of their own conscience.\n-- C.S. Lewis",
        "Fools! Don't they know that tears are a woman's most effective weapon?\n-- Catwoman (The Batman TV Series, episode 83)",
        "It's like a condom; I'd rather have it and not need it than need it and\nnot have it.\n-- some chick in Alien vs. Predator, when asked why she\nalways carries a gun",
        "C++ is history repeated as tragedy. Java is history repeated as farce.\n-- Scott McKay",
        "Simplicity takes effort-- genius, even.\n-- Paul Graham",
        "Show, don't tell.\n-- unknown",
        "In God I trust; I will not be afraid. What can mortal man do to me?\n-- David (Psalm 56:4)",
        "Linux is only free if your time has no value.\n-- Jamie Zawinski",
        "Code is poetry.\n-- wordpress.org",
        "If you choose not to decide, you still have made a choice.\n-- Rush (Freewill)",
        "Civilization advances by extending the number of important operations\nwhich we can perform without thinking about them.\n-- Alfred North Whitehead (Introduction to Mathematics)		",
        "The function of wisdom is to discriminate between good and evil.\n-- Cicero",
        "The reason to do animation is caricature. Good caricature picks out the\nessense of the statement and removes everything else. It's not simply\nabout reproducing reality; It's about bumping it up.\n-- Brad Bird, writer and director, The Incredibles",
        "Mistakes were made.\n-- Ronald Reagan",
        "I would rather be an optimist and be wrong than a pessimist who proves\nto be right. The former sometimes wins, but never the latter.\n-- \"Hoots\"",
        "What is truth?\n-- Pontius Pilate",
        "Life moves pretty fast. If you don't stop and look around once in a\nwhile, you could miss it.\n-- Ferris Bueller",
        "Lisp is worth learning for the profound enlightenment experience you\nwill have when you finally get it; that experience will make you a\nbetter programmer for the rest of your days, even if you never actually\nuse Lisp itself a lot.\n-- Eric S. Raymond",
        "Any sufficiently complicated C or Fortran program contains an ad hoc,\ninformally specified, bug-ridden, slow implementation of half of Common\nLisp.\n-- Philip Greenspun (Greenspun's Tenth Rule)",
        "I was talking recently to a friend who teaches at MIT. His field is hot\nnow and every year he is inundated by applications from would-be\ngraduate students. \"A lot of them seem smart,\" he said. \"What I can't\ntell is whether they have any kind of taste.\"\n-- Paul Graham",
        "The direct pursuit of happiness is a recipe for an unhappy life.\n-- Donald Campbell",
        "It's no trick for talented people to be interesting, but it's a gift to\nbe interested. We want an organization filled with interested people.\n-- Randy S. Nelson (dean of Pixar University)",
        "Why teach drawing to accountants? Because drawing class doesn't just\nteach people to draw. It teaches them to be more observant. There's no\ncompany on earth that wouldn't benefit from having people become more\nobservant.\n-- Randy S. Nelson (dean of Pixar University)",
        "All problems in computer science can be solved by another level of\nindirection.\n-- Butler Lampson	",
        "A designer knows he has arrived at perfection not when there is no\nlonguer anything to add, but when there is no longuer anything to take\naway.\n-- Antoine de St Exupery.",
        "For the things we have to learn before we can do them, we learn by doing\nthem.\n-- Aristotle.",
        "There are many ways to avoid success in life, but the most sure-fire\njust might be procrastination.\n-- Hara Estroff Marano.",
        "PI seconds is a nanocentury.\n-- [fact]",
        "A non negative binary integer value x is a power of 2 iff (x & (x-1)) is\n0 using 2's complement arithmetic.\n-- [fact]",
        "While I’ve always appreciated beautiful code, I share Jonathan’s concern\nabout studying it too much. I think studying beauty in music and\npainting has led us to modern classical music and painting that the\nmajority of us just don’t get. Beauty can be seen when it emerges, but\nisn’t something to strive for in isolation of a larger context. In the\nsoftware world, the larger context would be the utility of the software\nto the end user.\n-- [A comment on a blog]",
        "Dont give users the opportunity to lock themselves.\n-- unknown",
        "Any fool can make the simple complex, only a smart person can make the\ncomplex simple.\n-- unknown",
        "To do something well you have to love it. So to the extent you can\npreserve hacking as something you love, you're likely to do it well. Try\nto keep the sense of wonder you had about programming at age 14. If\nyou're worried that your current job is rotting your brain, it probably\nis.\n-- Paul Graham.",
        "- If you give him a penny for his thoughts, you'd get change.\n- Not the sharpest knife in the drawer.\n- A prime candidate for natural deselection.\n-- [Ideas for flamewars]",
        "What I didn't understand was that the value of some new acquisition\nwasn't the difference between its retail price and what I paid for it.\nIt was the value I derived from it. Stuff is an extremely illiquid\nasset. Unless you have some plan for selling that valuable thing you got\nso cheaply, what difference does it make what it's \"worth?\" The only way\nyou're ever going to extract any value from it is to use it. And if you\ndon't have any immediate use for it, you probably never will.\n-- Paul Graham",
        "Only bad designers blame their failings on the users.\n-- unknown",
        "Humans aren't rational -- they rationalize. And I don't just mean \"some\nof them\" or \"other people\". I'm talking about everyone. We have a \"logic\nengine\" in our brains, but for the most part, it's not the one in the\ndriver's seat -- instead it operates after the fact, generating\nrationalizations and excuses for our behavior.\n-- Paul Buchheit",
        "What do Americans look for in a car? I've heard many answers when I've\nasked this question. The answers include excellent safety ratings, great\ngas mileage, handling, and cornering ability, among others. I don't\nbelieve any of these. That's because the first principle of the Culture\nCode is that the only effective way to understand what people truly mean\nis to ignore what they say. This is not to suggest that people\nintentionally lie or misrepresent themselves. What it means is that,\nwhen asked direct questions about their interests and preferences,\npeople tend to give answers they believe the questioner wants to hear.\nAgain, this is not because they intend to mislead. It is because people\nrespond to these questions with their cortexes, the parts of their\nbrains that control intelligence rather than emotion or instinct. They\nponder a question, they process a question, and when they deliver an\nanswer, it is the product of deliberation. They believe they are telling\nthe truth. A lie detector would confirm this. In most cases, however,\nthey aren't saying what they mean.\n-- The culture code.",
        "When all you have is a hammer, everything looks like a nail.\n-- unknown",
        "Good coders code, great reuse.\n-- http://www.catonmat.net",
        "The lesson of the story might appear to be that self-interested and\nambitious people in power are often the cause of wastefulness in\ndeveloping countries. But self-interested and ambitious people are in\npositions of power, great and small, all over the world. In many places,\nthey are restrained by the law, the press, and democratic opposition.\nCameroon's tragedy is that there is nothing to hold self-interest in\ncheck.\n-- Tim Harford",
        "To solve your problems you must learn new skills, adapt new thought\npatterns, and become a different person than you were before that\nproblem.  God has crafted you for success. In the middle of every\nadversity lie your best opportunities. Discover it, build upon it and\nmove forward in your journey to live an extraordinary life.  You owe it\nto yourself to live a great life. Don’t let negative thoughts pull you\ndown. Be grateful and open to learn and grow.\n-- http://secretsofstudying.com/",
        "If there is a will, there is a way.\n-- unknown",
        "Having large case statements in an object-oriented language is a sure\nsign your design is flawed.\n-- [Fixing architecture flaws in Rails' ORM]",
        "Being a programmer is the same way. The only way to be a good programmer\nis to write code. When you realize you haven't been writing much code\nlately, and it seems like all you do is brag about code you wrote in the\npast, and people start looking at you funny while you're shooting your\nmouth off, realize it's because they know. They might not even know they\nknow, but they know. So, yes, doing what you love brings success, and by\nall means, throw yourself a nice big party, buy yourself a nice car,\nsoak up the adulation of an adoring crowd. Then shut the fuck up and get\nback to work.\n-- Sincerity Theory",
        "Another feature about this guy is his low threshold of boredom. He'll\npick up on a task and work frantically at it, accomplishing wonders in a\nshort time and then get bored and drop it before its properly finished.\nHe'll do nothing but strum his guitar and lie around in bed for several\ndays after.  Thats also part of the pattern too; periods of frenetic\nactivity followed by periods of melancholia, withdrawal and inactivity.\nThis is a bipolar personality.\n-- The bipolar lisp programmer",
        "My dream is that people adopt it on its own merits. We're not trying to\nbend Ruby on Rails to fit the enterprise, we're encouraging enterprises\nto bend to Ruby on Rails. Come if you like it, stay away if you don't.\nWe're not going head over heels to accommodate the enterprise or to lure\nthem away from Java. That's how you end up with Java, if you start\nbending to special interest groups.\n-- David Heinemeier Hansson (Ruby On Rails' creator)",
        "New eyes have X-ray vision.  [someone that hasn't written it is more\nlikely to spot the bug. \"someone\" can be you after a break]\n-- William S. Annis",
        "So - what are the most important problems in software engineering? I’d\nanswer “dealing with complexity”.\n-- Mark Chu-Carroll",
        "So the mere constraint of staying in regular contact with us will push\nyou to make things happen, because otherwise you'll be embarrassed to\ntell us that you haven't done anything new since the last time we\ntalked.\n-- Paul Graham (a talk at Y Combinator, for startup creators).",
        "The choice of the university is mostly important for the piece of paper\nyou get at the end. The education you get depends on you.\n-- Andreas Zwinkau",
        "Remember that you are humans in the first place and only after that\nprogrammers.\n-- Alexandru Vancea",
        "Humans differ from animals to the degree that they are not merely an end\nresult of their conditioning, but are able to reflect on their\nexperiences and strategies, and apply insight to make changes in the way\nthey live to modify the outcome.\n-- SlideTrombone (comment on \"Programming can ruin your life\")",
        "As builders and creators finding the perfect solution should not be our\nmain goal. We should find the perfect problem.\n-- Isaac (blog comment)",
        "Just like carpentry, measure twice cut once.\n-- Super-sizing YouTube with Python (Mike Solomon, mike@youtube.com)",
        "The good thing about reinventing the wheel is that you get a round one.\n-- Douglas Crockford (Author of JSON and JsLint)",
        "I feel it is everybodies obligation to reach for the best in themselves\nand use that for the interest of mankind.\n-- Corneluis (comment on 'Are you going to change the world? (Really?)')",
        "Abstraction is a form of data compression: absolutely necessary, because\nhuman short-term memory is so small, but the critically important aspect\nof abstraction is the algorithm that gets you from the name back to the\n\"uncompressed\" details.\n-- Bruce Wilder (blog post comment)",
        "Have you ever noticed that when you sit down to write something, half\nthe ideas that end up in it are ones you thought of while writing it?\nThe same thing happens with software. Working to implement one idea\ngives you more ideas.\n-- Paul Graham, The other road ahead.",
        "In general, we can think of data as defined by some collection of\nselectors and constructors, together with specified conditions that\nthese procedures must fulfill in order to be a valid representation.\n-- SICP, What is meant by data?",
        "Resume writing is just like dating, or applying for a bank loan, in that\nnobody wants you if you're desperate.\n-- Steve Yegge.",
        "Mastering isn’t a survival instinct; it’s an urge to excel. Mastering is\none of the experiences that delineates us from animals. It is striving\nto be more tomorrow than we are today; to perfectly pitch the ball over\nhome plate; to craft the perfect sentence in an article; to open the\noven and feel the warm, richly-scented cloud telling you dinner is going\nto be absolutely extraordinary. We humans crave perfection, to be\nmasters of our domain, to distinguish ourselves by sheer skill and\nprowess.\n-- Joesgoals.com",
        "It(mastering)’s knowing what you are doing.\n-- Joesgoals.com",
        "Well then. How could you possibly live without automated refactoring\ntools? How else could you coordinate the caterpillar-like motions of all\nJava’s identical tiny legs, its thousands of similar parts?\nI’ll tell you how:\nRuby is a butterfly.\n-- Stevey, Refactoring Trilogy, Part 1.",
        "You will never become a Great Programmer until you acknowledge that you\nwill always be a Terrible Programmer.\nYou will remain a Great Programmer for only as long as you acknowledge\nthat you are still a Terrible Programmer.\n-- Marc (http://kickin-the-darkness.blogspot.com/)",
        "If I tell you I'm good, you would probably think I'm boasting. If I tell\nyou I'm no good, you know I'm lying.\n-- Bruce Lee",
        "Let me try to get this straight: Lisp is a language for describing\nalgorithms. This was JohnMcCarthy's original purpose, anyway: to build\nsomething more convenient than a Turing machine. Lisp is not about file,\nsocket or GUI programming - Lisp is about expressive power. (For\nexample, you can design multiple object systems for Lisp, in Lisp. Or\nimplement the now-fashionable AOP. Or do arbitrary transformations on\nparsed source code.) If you don't value expressive power, Lisp ain't for\nyou. I, personally, would prefer Lisp to not become mainstream: this\nwould necessarily involve a dumbing down.\n-- VladimirSlepnev",
        "Je ne vous impose aucune contrainte, aucune limite. Surprenez-moi,\nétonnez-moi, défiez-moi, défiez-vous vous-même. Vous avez le choix: vous\npouvez rester dans l'ombre ou en sortir en étant parmis les trop rares\nexceptions à avoir réussi. L'heure est venue d'aller bien au delà de\nvotre potentiel. L'heure est venue maintenant de descendre vraiment en\nvous. L'heure est venue de démontrer pourquoi vous êtes l'élite, les\nquelques élus, les rares lueurs qui offrent à cette compagnie son\ncaractère exceptionnel, sa luminescence.\n-- Le PDG de NURV, dans \"Anti-trust\".",
        "If something isn’t working, you need to look back and figure out what\ngot you excited in the first place.\n-- David Gorman (ImThere.com)",
        "Opportunities that present themselves to you are the consequence -- at\nleast partially -- of being in the right place at the right time. They\ntend to present themselves when you're not expecting it -- and often\nwhen you are engaged in other activities that would seem to preclude you\nfrom pursuing them. And they come and go quickly -- if you don't jump\nall over an opportunity, someone else generally will and it will vanish.\n-- Marc Andreessen (http://blog.pmarca.com/)",
        "Pay attention to opportunity cost at all times. Doing one thing means\nnot doing other things. This is a form of risk that is very easy to\nignore, to your detriment.\n-- Marc Andreessen (http://blog.pmarca.com/)",
        "Seize any opportunity, or anything that looks like opportunity. They are\nrare, much rarer than you think...\n-- Nassim Nicholas Taleb, \"The Black Swan\".",
        "I think that a lot of programmers are ignoring an important point when\npeople talk about reducing code repetition on large projects.\nPart of the idea is that large projects are intrinsically *wrong*. That\nyou should be looking at making a number of smaller projects that are\ncomposable, even if you never end up reusing one of those smaller\nprojects elsewhere.\n-- Dan Nugent",
        "We tend to seek easy, single-factor explanations of success. For most\nimportant things, though, success actually requires avoiding many\nseparate causes of failure.\n-- Jared Diamond",
        "Things which matter most must never be at the mercy of things which\nmatter least.\n-- Johann Wolfgang Von Goethe (1749-1832)",
        "I think the root of your mistake is saying that macros don't scale to\nlarger groups. The real truth is that macros don't scale to stupider\ngroups.\n-- Paul Graham, on the Lightweight Languages mailing list.",
        "Argue with idiots, and you become an idiot.\nIf you compete with slaves you become a slave.\n-- Paul Graham and Norbert Weiner, respectively",
        "Always dive down into a problem and get your hands on the deepest issue\nbehind the problem. All other considerations are to dismissed as\n\"engineering details\"; they can be sorted out after the basic problem\nhas been solved.\n-- Chris Crawford",
        "Don't have good ideas if you aren't willing to be responsible for them.\n-- Alan Perlis",
        "It is impossible to sharpen a pencil with a blunt axe. It is equally\nvain to try to do it with ten blunt axes instead. \n-- Edsger Dijkstra",
        "If we wish to count lines of code, we should not regard them as lines\nproduced but as lines spent.\n-- Edsger Dijkstra",
        "The most damaging phrase in the language is, It's always been done that\nway.\n-- Rear Admiral Grace Hopper",
        "Getting back to failing early, I've learned it's important to completely\nfail. Get fired. Shoot the project, then burn its corpse. Melt the CVS\nrepository and microwave the backup CDs. When things go wrong, I've\noften tried to play the hero from start to finish. Guess what? Some\nprojects are doomed no matter what. Some need skills I don't possess.\nAnd some need a fresh face.\n-- Reginald Braithwaite",
        "The only thing a man should ever be 100% convinced of is his own\nignorance.\n-- DJ MacLean",
        "The best people and organizations have the attitude of wisdom: The\ncourage to act on what they know right now and the humility to change\ncourse when they find better evidence.\nThe quest for management magic and breakthrough ideas is overrated;\nbeing a master of the obvious is underrated.\nJim Maloney is right: Work is an overrated activity\n-- Bob Sutton",
        "In theory, there’s no difference between theory and practice. But in\npractice, there is.\n-- Albert Einstein",
        "Act from reason, and failure makes you rethink and study harder.\nAct from faith, and failure makes you blame someone and push harder.\n--  Erik Naggum",
        "Measure everything you can about the product, and you'll start seeing\npatterns.\n-- Max Levchin, PayPal founder, Talk at StartupSchool2007",
        "Something Confusing about \"Hard\":\nIt's tempting to think that if it's hard, then it's valuable.\nMost valuable things are hard.\nMost hard things are completely useless -- (picture of someone smashing\ntheir head through concrete blocks kung-fu style).\nHard DOES NOT EQUATE TO BEING valuable.\nRemember Friendster back in the day?\nYou'd sign in, invite friends, have 25 friends, go to their profile, and\nthen it'd show how you were connected to each one.\nThat's an impressive [some geeky CS jargon] Cone traversal of a tree -\n100 million string comparisons per page -- it won't scale.\nUsed to take a minute per page to load, and Friendster died a painful\ndeath.\nMySpace -- not interested in solving problems\nThey use the shortcut of \"Miss Fitzpatrick is in your extended network\"\n(i.e. even when you're not even signed up for MySpace)\nThey didn't solve the hard problem. But they make the more relevant\nassumption that you want to be connected to hot women. [LOL]\nShows Alexa graph showing that in early 2005 Myspace took off, and\nquickly bypassed Friendster and never looked back.\n-- Max Levchin, PayPal founder, Talk at StartupSchool2007",
        "Quality of the people is better than the quality of the business idea.\nCrappy people can screw up the best idea in the world.\n-- Hadi Partovi & Ali Partovi (iLike.com), Talk at StartupSchool2007",
        "The only constant in the world of hi-tech is change.\n-- Mark Ward",
        "Write it properly first. It's easier to make a correct program fast,\nthan to make a fast program correct.\n-- http://www.cpax.org.uk/prg/",
        "J'ai toujours préféré la folie des passions à la sagesse de\nl'indifférence.\n-- Anatole France",
        "You can’t get to version 500 if you don’t start with a version 1.\n-- BetterExplained.com",
        "The wonderful and frustrating thing about understanding yourself is that\nnobody can do it for you.\n-- BetterExplained.com",
        "When you have eliminated the impossible, whatever remains, however\nimprobable, must be the truth.\n-- Sherlock Holmes",
        "In order to understand what another person is saying, you must assume\nthat it is true and try to find out what it could be true of.\n-- George Miller",
        "A journey of a thousand miles must begin with a single step.\n-- Lao­Tzu",
        "C’s great for what it’s great for.\n-- Ben Hoyts (micropledge)",
        "There is one meaning [for static in C]: a global variable that is\ninvisible outside the current scope, be it a function or a file.\n-- Paolo Bonzini",
        "Processors don't get better so that they can have more free time.\nProcessors get better so _you_ can have more free time.\n-- LeCamarade (freeshells.ch)",
        "The venerable master Qc Na was walking with his student, Anton.  Hoping to\nprompt the master into a discussion, Anton said \"Master, I have heard that\nobjects are a very good thing - is this true?\"  Qc Na looked pityingly at\nhis student and replied, \"Foolish pupil - objects are merely a poor man's\nclosures.\"\n    Chastised, Anton took his leave from his master and returned to his cell,\nintent on studying closures.  He carefully read the entire \"Lambda: The\nUltimate...\" series of papers and its cousins, and implemented a small\nScheme interpreter with a closure-based object system.  He learned much, and\nlooked forward to informing his master of his progress.\n    On his next walk with Qc Na, Anton attempted to impress his master by\nsaying \"Master, I have diligently studied the matter, and now understand\nthat objects are truly a poor man's closures.\"  Qc Na responded by hitting\nAnton with his stick, saying \"When will you learn? Closures are a poor man's\nobject.\"  At that moment, Anton became enlightened.\n-- Anton van Straaten (Na = Norman Adams, Qa = Christian Queinnec)",
        "Understanding why C++ is the way it is helps a programmer use it well. A deep\nunderstanding of a tool is essential for an expert craftsman.\n-- Bjarne Stroustrap",
        "No art, however minor, demands less than total dedication if you want to\nexcel in it.\n-- Alberti",
        "The minute you put the blame on someone else you’ve switch things from\nbeing a problem you can control to a problem outside of your control.\n-- engtech (internetducttape.com)",
        "State is the root of all evil. In particular functions with side effects\nshould be avoided.\n-- OO Sucks (bluetail.com)",
        "Ils ne sont pas forts parce qu'ils sont forts. Ils sont forts parce que\nnous sommes faibles.\n-- Ragala Khalid",
        "It is better to be quiet and thought a fool than to open your mouth and\nremove all doubt.\n-- WikiHow",
        "A tail call allows a function to return the result of another function\nwithout leaving an entry on the stack. Tail recursion is a specific case\nof tail calling.\n-- ASPN : Python Cookbook : Explicit Tail Call",
        "Simplicity means the achievement of maximum effect with minimum means.\n-- Dr. Koichi Kawana",
        "Normality is the route to nowhere.\n-- Ridderstrale & Nordstorm, Funky Business",
        "The problem is that Microsoft just has no taste. And I don't mean that\nin a small way, I mean that in a big way.\n-- Steve Jobs",
        "Do you want to sell sugared water all your life or do you want to change\nthe world?\n-- Steve Jobs, to John Sculley (former Pepsi executive)",
        "1 - Creativity and innovation always build on the past.\n2 - The past always tries to control the creativity that builds on it.\n3 - Free societies enable the future by limiting the past.\n4 - Ours is less and less a free society.\n-- Lawrence Lessig, Free Culture.",
        "Good work is no done by ‘humble’ men.\n-- H. Hardy, A mathematician's apology.",
        "Simplicity and pragmatism beat complexity and theory any day.\n-- Dennis (blog comment)",
        "The proof is by reductio ad absurdum, and reductio ad absurdum, which\nEuclid loved so much, is one of a mathematician’s finest weapons. It is\na far finer gambit than any chess gambit: a chess player may offer the\nsacrifice of a pawn or even a piece, but a mathematician offers the\ngame.\n-- G. H. Hardy",
        "Remember, always be yourself ... unless you suck!\n-- Joss Whedon",
        "All great things require great dedication.\n-- Chuck Norris(?)",
        "I'm always happy to trade performance for readability as long as the\nformer isn't already scarce.\n-- Crayz (Commentor on blog.raganwald.com)",
        "You have to write for your audience. I would never write (1..5).map\n&'*2' in Java when I could write\nListFactoryFactory.getListFactoryFromResource(\n    new ResourceName('com.javax.magnitudes.integers').\nsetLowerBound(1).setUpperBound(5).setStep(1).applyFunctor(\n    new Functor () { public void eval (x) { return x * 2; } }))\nI'm simplifying, of course, I've left out the security and logging\nwrappers.\n-- Reginald Braithwait",
        "The definition of insanity is doing the same thing over and over again\nand expecting different results.\n-- Benjamin Franklin",
        "A no uttered from the deepest conviction is better than a yes merely\nuttered to please or what is worse, to avoid trouble.\n-- Mahatma Gandhi",
        "I think it is wise, and only honest, to warn you that my goal is\nimmodest. It is not my purpose to \"transfer knowledge\" to you that,\nsubsequently, you can forget again. My purpose is no less than to\neffectuate in each of you a noticeable, irreversable change. I want you\nto gain, for the rest of your lives, the insight that beautiful proofs\nare not \"found\" by trial anf error but are the result of a consciously\napplied design discipline. I want you to raise your quality standards. I\nmean, if 10 years from now, when you are doing something quick and\ndirty, you suddenly visualize that I am looking over your shoulders and\nsay to yourself \"Dijkstra would not have liked this\", well, that would\nbe enough immortality for me.\n-- E. W. Dijkstra",
        "The general principle for complexity design is this: Think locally, act\nlocally.\n-- Richard P. Gabriel & Ron Goldman, Mob Software: The Erotic Life of Code",
        "Programming is the art of figuring out what you want so precisely that\neven a machine can do it.\n-- Some guy who isn't famous",
        "Hence my urgent advice to all of you to reject the morals of the\nbestseller society and to find, to start with, your reward in your own\nfun. This is quite feasible, for the challenge of simplification is so\nfascinating that, if we do our job properly, we shall have the greatest\nfun in the world.\n-- E. W. Dijkstra, On the nature of computing science.",
        "Remember: you are alone. Every time you can get help from someone,\nit is an opportunity: you should eagerly size it. But then, promptly\nreturn to normal mode: you are alone and you must be prepared to solve\nevery problem yourself.\n-- Eric KEDJI",
        "Making All Software Into Tools Reduces Risk.\n-- smoothspan.com",
        "Some may say Ruby is a bad rip-off of Lisp or Smalltalk, and I admit\nthat. But it is nicer to ordinary people.\n-- Matz, LL2",
        "C and Lisp stand at opposite ends of the spectrum; they're each great at\nwhat the other one sucks at.\n-- Steve Yegge, Tour de Babel.",
        "Two people should stay together if together they are better people than\nthey would be individually.\n-- ?",
        "To the optimist, the glass is half full. To the pessimist, the glass is\nhalf empty. To the engineer, the glass is twice as big as it needs to\nbe.\n-- author unknown (quoted in `Robust Systems', Gerald Jay Suseman)",
        "It is practically impossible to teach good programming to students that\nhave had a prior exposure to BASIC: as potential programmers they are\nmentally mutilated beyond hope of regeneration.\n-- Edsger Dijkstra",
        "Whatever is worth doing at all, is worth doing well.\n-- Earl of Chesterfield",
        "Rules of Optimization:\nRule 1: Don’t do it.\nRule 2 (for experts only): Don’t do it yet.\n-- M.A. Jackson",
        "More computing sins are committed in the name of efficiency (without\nnecessarily achieving it) than for any other single reason - including\nblind stupidity.\n-- W.A. Wulf",
        "We should forget about small efficiencies, say about 97% of the time:\npremature optimization is the root of all evil.\n-- Donald Knuth",
        "The best is the enemy of the good.\n-- Voltaire",
        "The job of a leader today is not to create followers. It’s to create\nmore leaders.\n-- Ralph Nader",
        "The president was visiting NASA headquarters and stopped to talk to a\nman who was holding a mop. “And what do you do?” he asked. The man, a\njanitor, replied, “I’m helping to put a man on the moon, sir.”\n-- The little book of leadership",
        "Only make new mistakes.\n-- Phil Dourado",
        "You can recognize truth by its beauty and simplicity. When you get it\nright, it is obvious that it is right.\n-- Richard Feynman",
        "Talkers are no good doers.\n-- William Shakespeare, \"Henry VI\"",
        "Photography is painting with light.\n-- Eric Hamilton",
        "Good artists copy. Great artists steal.\n-- Pablo Picasso",
        "A guideline in the process of stepwise refinement should be the\nprinciple to decompose decisions as much as possible, to untangle\naspects which are only seemingly interdependent, and to defer those\ndecisions which concern details of representation as long as possible.\n-- Niklaus Wirth",
        "Vigorous writing is concise. A sentence should contain no unnecessary\nwords, a paragraph no unnecessary sentences, for the same reason that a\ndrawing should have no unnecessary lines and a machine no unnecessary\nparts. This requires not that the writer make all sentences short or\navoid all detail and treat subjects only in outline, but that every word\ntell.\n-- William Strunk, Jr. (The Elements of Style)",
        "The problem is that small examples fail to convince, and large examples\nare too big to follow.\n-- Steve Yegge.",
        "We are the sum of our behaviours; excellence therefore is not an act but\na habit.\n-- Aristotle.",
        "The purpose of abstraction is not to be vague, but to create a new\nsemantic level in which one can be absolutely precise.\n-- Edsger Dijkstra",
        "Every man prefers belief to the exercise of judgment.\n-- Seneca",
        "It’s hard to grasp abstractions if you don’t understand what they’re\nabstracting away from.\n-- Nathan Weizenbaum",
        "That is one of the most distinctive differences between school and the\nreal world: there is no reward for putting in a good effort. In fact,\nthe whole concept of a \"good effort\" is a fake idea adults invented to\nencourage kids. It is not found in nature.\n-- Paul Graham",
        "I find that the harder I work, the more luck I seem to have.\n-- Thomas Jefferson",
        "Don't stay in bed, unless you can make money in bed.\n-- George Burns",
        "If everything seems under control, you're not going fast enough.\n-- Mario Andretti",
        "Chance favors the prepared mind.\n-- Louis Pasteur",
        "Controlling complexity is the essence of computer programming.\n-- Brian Kernigan",
        "The function of good software is to make the complex appear to be\nsimple.\n-- Grady Booch",
        "Programmers are in a race with the Universe to create bigger and better\nidiot-proof programs, while the Universe is trying to create bigger and\nbetter idiots.  So far the Universe is winning.\n-- Rich Cook",
        "A hacker on a roll may be able to produce–in a period of a few\nmonths–something that a small development group (say, 7-8 people) would\nhave a hard time getting together over a year.  IBM used to report that\ncertain programmers might be as much as 100 times as productive as other\nworkers, or more.\n-- Peter Seebach",
        "The best programmers are not marginally better than merely good ones.\nThey are an order-of-magnitude better, measured by whatever standard:\nconceptual creativity, speed, ingenuity of design, or problem-solving\nability.\n-- Randall E. Stross",
        "A great lathe operator commands several times the wage of an average\nlathe operator, but a great writer of software code is worth 10,000\ntimes the price of an average software writer.\n-- Bill Gates",
        "Measuring programming progress by lines of code is like measuring\naircraft building progress by weight.\n-- Bill Gates",
        "First learn computer science and all the theory.  Next develop a\nprogramming style.  Then forget all that and just hack.\n-- George Carrette",
        "To iterate is human, to recurse divine.\n-- L. Peter Deutsch",
        "The best thing about a boolean is even if you are wrong, you are only\noff by a bit.\n-- Anonymous",
        "Should array indices start at 0 or 1?  My compromise of 0.5 was rejected\nwithout, I thought, proper consideration.\n-- Stan Kelly-Bootle",
        "The use of COBOL cripples the mind; its teaching should therefore be\nregarded as a criminal offense.\n-- E.W. Dijkstra",
        "It is practically impossible to teach good programming style to students\nthat have had prior exposure to BASIC.  As potential programmers, they\nare mentally mutilated beyond hope of regeneration.\n-- E. W. Dijkstra",
        "One of the main causes of the fall of the Roman Empire was that–lacking\nzero–they had no way to indicate successful termination of their C\nprograms.\n-- Robert Firth",
        "Saying that Java is nice because it works on all OSes is like saying\nthat anal sex is nice because it works on all genders.\n-- Alanna",
        "If Java had true garbage collection, most programs would delete\nthemselves upon execution.\n-- Robert Sewell",
        "Software is like sex: It’s better when it’s free.\n-- Linus Torvalds",
        "Any code of your own that you haven’t looked at for six or more months\nmight as well have been written by someone else.\n-- Eagleson’s Law",
        "Good programmers use their brains, but good guidelines save us having to\nthink out every case.\n-- Francis Glassborow",
        "Considering the current sad state of our computer programs, software\ndevelopment is clearly still a black art, and cannot yet be called an\nengineering discipline.\n-- Bill Clinton",
        "If debugging is the process of removing bugs, then programming must be\nthe process of putting them in.\n-- Edsger W. Dijkstra",
        "Always code as if the guy who ends up maintaining your code will be a\nviolent psychopath who knows where you live.\n-- Martin Golding",
        "Everything that can be invented has been invented.\n-- Charles H. Duell, Commissioner, U.S. Office of Patents, 1899",
        "I think there’s a world market for about 5 computers.\n-- Thomas J. Watson, Chairman of the Board, IBM, circa 1948",
        "It would appear that we have reached the limits of what it is possible\nto achieve with computer technology, although one should be careful with\nsuch statements, as they tend to sound pretty silly in 5 years. \n-- John Von Neumann, circa 1949",
        "But what is it good for?\n-- Engineer at the Advanced Computing Systems Division of IBM,\ncommenting on the microchip, 1968",
        "There is no reason for any individual to have a computer in his home.\n-- Ken Olson, President, Digital Equipment Corporation, 1977",
        "640K ought to be enough for anybody.\n-- Bill Gates, 1981",
        "Windows NT addresses 2 Gigabytes of RAM, which is more than any\napplication will ever need.\n-- Microsoft, on the development of Windows NT, 1992",
        "We will never become a truly paper-less society until the Palm Pilot\nfolks come out with WipeMe 1.0.\n-- Andy Pierson",
        "If it keeps up, man will atrophy all his limbs but the push-button\nfinger.\n-- Frank Lloyd Wright",
        "Functional programming is like describing your problem to a\nmathematician.  Imperative programming is like giving instructions to\nan idiot.\n-- arcus, #scheme on Freenode",
        "Its a shame that the students of our generation grew up with windows and\nmice because that tainted our mindset not to think in terms of powerful\ntools. Some of us are just so tainted that we will never recover.\n-- Jeffrey Mark Siskind <qobi@research.nj.nec.com> in comp.lang.lisp",
        "Lisp is a programmable programming language.\n-- John Foderaro",
        "I guess, when you're drunk, every woman looks beautiful and every\nlanguage looks (like) a Lisp :)\n-- Lament, #scheme@freenode.net",
        "Many of life's failures are people who did not realize how close they\nwere to success when they gave up.\n-- Thomas Edison",
        "You must always work not just within but below your means. If you can\nhandle three elements, handle only two. If you can handle ten, then\nhandle five. In that way the ones you do handle, you handle with more\nease, more mastery and you create a feeling of strength in reserve.\n-- Pablo Picasso",
        "When you’ve got the code all ripped apart, it’s like a car that’s all\ndisassembled. You’ve got all the parts tying all over your garage and\nyou have to replace the broken part or the car will never run. It’s not\nfun until the code gets back to the baseline again.\n-- Gary Kildall (inventor of CP/M, one of the first OS for the micro).",
        "\nWell, if you talk about programming to a group of programmers who use\nthe same language, they can become almost evangelistic about the\nlanguage. They form a tight-knit community, hold to certain beliefs, and\nfollow certain rules in their programming. It’s like a church with a\nprogramming language for a Bible.\n-- Gary Kildall (inventor of CP/M, one of the first OS for the micro).",
        "It’s a problem if the design doesn’t let you add features at a later\ndate. If you have to redo a program, the hours you spend can cause you\nto lose your competitive edge. A flexible program demonstrates the\ndifference between a good designer and someone who is just getting a\npiece of code out.\n-- Gary Kildall (inventor of CP/M, one of the first OS for the micro).",
        "[How friendly will this machine be?] Well, I don’t think it’s a matter\nof friendliness, because ultimately if the program is going to\naccomplish anything of value, it will probably be relatively complex.\n-- Gary Kildall (inventor of CP/M, one of the first OS for the micro).",
        "Some people suggest that machines would be friendlier if input could be\nin a natural language. But natural language is probably the worst kind\nof input because it can be quite ambiguous. The process of retrieving\ninformation from the computer would be so time-consuming that you would\nbe better off spending that time getting the information directly from\nan expert.\n-- Gary Kildall (inventor of CP/M, one of the first OS for the micro).",
        "The only way of discovering the limits of the possible is to venture a\nlittle way past them into the impossible.\n-- Arthur C. Clarke",
        "Any sufficiently advanced technology is undistinguishable from magic.\n-- Arthur C. Clarke",
        "That is the inevitable human response. We’re reluctant to believe that\ngreat discoveries are in the air. We want to believe that great\ndiscoveries are in our heads—and to each party in the multiple the\npresence of the other party is invariably cause for suspicion.\n-- Malcolm Gladwell, Who says big ideas are rare? ",
        "Good ideas are out there for anyone with the wit and the will to find\nthem.\n-- Malcolm Gladwell, Who says big ideas are rare?",
        "A person won't become proficient at something until he or she has done\nit many times. In other words., if you want someone to be really good at\nbuilding a software system, he or she will have to have built 10 or more\nsystems of that type.\n-- Philip Greenspun",
        "A person won't retain proficiency at a task unless he or she has at one\ntime learned to perform that task very rapidly. Learning research\ndemonstrates that the skills of people who become accurate but not fast\ndeteriorate much sooner than the skills of people who become both\naccurate and fast.\n-- Philip Greenspun",
        "Training research shows that if you get speed now you can get quality\nlater. But if you don't get speed you will never get quality in the long\nrun.\n-- Philip Greenspun",
        "Beware of bugs in the above code; I have only proved it correct, not\ntried it.\n-- Donald Knuth",
        "Wear your best for your execution and stand dignified. Your last\nrecourse against randomness is how you act — if you can’t control\noutcomes, you can control the elegance of your behaviour. You will\nalways have the last word.\n-- Nassim Taleb",
        "The human brain starts working the moment you are born and never stops\nuntil you stand up to speak in public.\n-- Anonymous",
        "The trouble with the world is that the stupid are always cocksure and\nthe intelligent are always filled with doubt.\n-- Bertrand Russell",
        "Simple, clear purpose and principles give rise to complex, intelligent\nbehavior. Complex rules and regulations give rise to simple, stupid\nbehavior.\n-- Dee Hock, Birth of the Chaordic Age",
        "C++ is like teenage sex: Everybody is talking about it all the time,\nonly few are really doing it.\n-- unknown",
        "Functional programming is to algorithms as the ubiquitous little black\ndress is to women's fashion.\n-- Mark Tarver (of \"The bipolar Lisp programmer\" fame)",
        "Java and C++ make you think that the new ideas are like the old ones.\nJava is the most distressing thing to hit computing since MS-DOS.\n-- Alan Kay",
        "For complex systems, the compiler and development environment need to be\nin the same language that its supporting. It's the only way to grow\ncode.\n-- Alan Kay",
        "Simple things should be simple. Complex things should be possible.\n-- Alan Kay",
        "I invented the term Object-Oriented, and I can tell you I did not have\nC++ in mind.\n-- Alan Kay",
        "All creativity is an extended form of a joke.\n-- Alan Kay",
        "If you don't fail at least 90 percent of the time, you're not aiming\nhigh enough.\n-- Alan Kay",
        "Revolutions come from standing on the shoulders of giants and facing in\na better direction.\n-- Alan Kay",
        "Ce n’est que par les beaux sentiments qu’on parvient à la fortune !\n-- Charles Baudelaire, Conseils aux jeunes littérateurs.",
        "La haine est une liqueur précieuse, un poison plus cher que celui des\nBorgia, - car il est fait avec notre sang, notre santé, notre sommeil,\net les deux tiers de notre amour! Il faut en être avare!\n-- Charles Baudelaire, Conseils aux jeunes littérateurs.",
        "L’art qui satisfait le besoin le plus impérieux sera toujours le plus\nhonoré.\n-- Charles Baudelaire, Conseils aux jeunes littérateurs.",
        "If it looks like a duck, walks like a duck, and quacks like a duck, it's\na duck.\n-- Official definition of \"duck typing\"",
        "In OO, it's the data that is the \"important\" thing: you define the class\nwhich contains member data, and only incidentally contains code for\nmanipulating the object. In FP, it's the code that's important: you\ndefine a function which contains code for working with the data, and\nonly incidentally define what the data is.\n-- almkgor, on reddit",
        "Des mots simples, quand ils sont bien utilisés, font faire à des gens\nordinaires des choses extraordinaires.\n-- Khaled TANGAO",
        "It was Edison who said ‘1% inspiration, 99% perspiration’. That may have\nbeen true a hundred years ago. These days it's ‘0.01% inspiration,\n99.99% perspiration’, and the inspiration is the easy part.\n-- Linux Torvalds",
        "The greatest challenge to any thinker is stating the problem in a way\nthat will allow a solution.\n-- Bertrand Russell",
        "No matter how much you plan you’re likely to get half wrong anyway. So\ndon’t do the ‘paralysis through analysis’ thing. That only slows\nprogress and saps morale.\n-- 37 Signal, Getting real",
        "[Innovation] comes from saying no to 1,000 things to make sure we don’t\nget on the wrong track or try to do too much. We’re always thinking\nabout new markets we could enter, but it’s only by saying no that you\ncan concentrate on the things that are really important.\n-- Steve Jobs",
        "The ability to simplify means to eliminate the unnecessary so that the\nnecessary may speak.\n-- Hans Hofmann",
        "However beautiful the strategy, you should occasionally look at the\nresults.\n-- Winston Churchill",
        "Genius is 1% inspiration and 99% perspiration.\n-- Thomas Edison",
        "I’d rather write programs to write programs than write programs.\n-- Richard Sites",
        "Heureux l'étudiant qui comme la Rivière peut suivre son cours sans\nquitter son lit...\n-- Sebastien, sur commentcamarche.net",
        "Side projects are less masturbatory than reading RSS, often more\nuseful than MobileMe, more educational than the comments on Reddit,\nand usually more fun than listening to keynotes.\n-- Chris Wanstrath",
        ":nunmap can also be used outside of a monastery.\n-- Vim user manual",
        "I had to learn how to teach less, so that more could be learned.\n-- Tim Gallwey, The inner game of work",
        "Workers of the world, the chains that bind you are not held in place by\na ruling class, a \"superior\" race, by society, the state, or a leader.\nThey are held in place by none other than yourself. Those who seek to\nexploit are not themselves free, for they place no value in freedom. Who\nis it that really employs you and commands you to pick up your daily\nload? And who is it that you allow to pass judgment on the adequacy of\nyour toil? Who have you empowered to dangle the carrot before you and\nthreaten with disapproval? Who, when you wake each morning, sends you\noff to what you call your work?\nIs there an \"I want to\" behind all your \"I have to,\" or have you been so\nlong forgotten to yourself that \"I want\" exists only as an idea in your\nhead? If you have disconnected from your soul's desire and are drowning\nin an ocean of \"have to,\" then rise up and overthrow your master. Begin\nthe journey toward emancipation.  Work only in such a way that you are\ntruly self-employed.\n-- Tim Gallwey, The inner game of work",
        "The Work Begins Anew, The Hope Rises Again, And The Dream Lives On.\n-- Ted Kennedy",
        "The hardest part of design ... is keeping features out.\n-- Donald Norman ",
        "Before software can be reusable it first has to be usable.\n-- Ralph Johnson ",
        "The opposite of love is not hate, it is indifference.\n-- Elie Wiesel",
        "- Gbi de fer\n- Howa!\n- On va en France\n- Non, je vais pas!\n- Pourquoi?\n- Parce ki y a pas agouti là-bas!\n-- Gbi de fer",
        "Ecoute, crois en ton projet... Implique toi à fond... Trouve des aspects\ninnovants pour te distinguer des autres. Tu verras que tu te feras\nremarquer très facilement...\n-- Khaled Tangao",
        "Perpetual optimism is a force multiplier.\n-- Colin Powell",
        "Be the change you want to see in the world.\n-- Mahatma Gandhi",
        "The art of getting someone else to do something you want done because he\nwants to do it [Leadership].\n-- Dwight D. Enseinhover.",
        "No one is all evil. Everybody has a good side. If you keep waiting, it\nwill comme up.\n-- Randy Pausch",
        "Experience is what you get when you don't get what you want.\n-- Cited by Randy Pausch",
        "Luck is where preparation meets opportunity.\n-- Randy Pausch",
        "Bonne bosse et reste le boss.\n-- Darryl Amedon",
        "The greatest of all weaknesses is the fear of appearing weak.\n-- J. B. Bossuet, Politics from Holy Writ, 1709",
        "It's easier to ask forgiveness than it is to get permission.\n-- Rear Admiral Dr. Grace Hopper",
        "An investment in knowledge always pays the best interest.\n-- Benjamin Franklin",
        "Natives who beat drums to drive off evil spirits are objects of scorn to\nsmart Americans who blow horns to break up traffic jams.\n-- Mary Ellen Kelly",
        "A CS professor once explained recursion as follows:\nA child couldn't sleep, so her mother told her a story about a little frog,\n    who couldn't sleep, so the frog's mother told her a story about a little bear,\n         who couldn't sleep, so the bear's mother told her a story about a little weasel...\n            who fell asleep.\n        ...and the little bear fell asleep;\n    ...and the little frog fell asleep;\n...and the child fell asleep.\n-- everything2.com",
        "Never do the impossible. People will expect you to do it forever after.\n-- pigsandfishes.com",
        "Hire people smarter than you.  Work with people smarter than you.\nListen to them. Let them lead you. Take the blame for all failures,\ngive away the credit for all successes.\n-- How to fail: 25 secrets learned through failure",
        "Give up control. You never really had it anyway.\n-- How to fail: 25 secrets learned through failure",
        "Ne te mets pas de limite, la vie se chargera de la mettre a ta place.\n-- Darryl AMEDON",
        "Only two things are infinite, the universe and human stupidity. And I'm not so\nsure about the former.\n-- Albert Einstein",
        "The important thing is not to stop questioning.\n-- Albert Einstein",
        "Do not accept anything because it comes from the mouth of a respected person.\n-- Buddha",
        "Work as intensely as you play and play as intensely as you work.\n-- Eric S. Raymond, How To Be A Hacker",
        "A witty saying proves nothing\n-- Voltaire",
        "Sound methodology can empower and liberate the creative mind; it cannot inflame\nor inspire the drudge.\n-- Frederick P. Brooks, No Sliver Bullet.",
        "La connaissance d'un défaut ne l'enlève pas, elle nous torture jusqu'à sa\ncorrection.\n-- Daniel Lovewin (Guillaume Kpotufe)",
        "Je crois au flooding.\n-- Karim BAINA (en parlant du dailogue avec les administrations)",
        "Il y a très loin de la velléité à la volnt, de la volonté à la résolution, de la\nrésolution au choix des moyens, du choix ds moyens à lapplication.\n-- Jean-François Paul de Gondi de Retz",
        "Do not spoil what you have by desiring what you have not; but remember that what\nyou now have was once among the things only hoped for.\n-- Greek philosopher Epicurus",
        "Nobody can make you feel inferior without your consent.\n-- Eleanor Roosevelt",
        "If you tell the truth, you don't have to remember anything.\n-- Mark Twain",
        "You know you're in love when you can't fall asleep because reality is finally\nbetter than your dreams.\n-- Dr. Seuss",
        "The opposite of love is not hate, it's indifference.\n-- Elie Wiesel",
        "Life is what happens to you while you're busy making other plans.\n-- John Lennon",
        "Whenever you find yourself on the side of the majority, it is time to pause and\nreflect.\n-- Mark Twain",
        "To be yourself in a world that is constantly trying to make you something else\nis the greatest accomplishment.\n-- Ralph Waldo Emerson",
        "It is not a lack of love, but a lack of friendship that makes unhappy marriages.\n-- Friedrich Nietzsche",
        "In terms of energy, it's better to make a wrong choice than none at all.\n-- George Leonard, Mastery.",
        "Courage is grace under pressure.\n-- Ernest Hemingway",
        "Actually, the essence of boredom is to be found in the obsessive search for\nnovelty. Satisfaction lies in mindful repetition, the discovery of endless\nrichness in subtle variations on familiar themes.\n-- George Leonard, Mastery.",
        "Before enlightenment, chop wood and carry water.\nAfter enlightenment, chop wood and carry water.\n-- Ancient Eastern adage",
        "Acknowledging the negative doesn't mean sniveling [whining, complaining]; it\nmeans facing the truth and then moving on.\n-- George Leonard, Mastery.",
        "Whatever you can do, or dream you can, begin it. Boldness has genius, power, and\nmagic in it.\n-- Goethe",
        "What we choose to fight is so tiny!\nWhat fights us is so great!\n...\nWhen we win it's with small things,\nand the triumph itself makes us small.\n...\nWinning does not tempt that man.\nThis is how he grows: by being defeated, decisively,\nby constantly greater beings. \n-- Rainer Maria Rilke, The Man Watching.",
        "We fail to realize that mastery is not about perfection. It's about a process,\na journey. The master is the one who stays on the path day after day, year after\nyear. The master is the one who is willing to try, and fail, and try again, for\nas long as he or she lives.\n-- George Leonard, Mastery.",
        "Are you willing to wear your white belt?\n-- George Leonard, Mastery."
};

static const char *qotdfs_path = "/quote";

#define qotd (quotes[(current_time.tm_yday - 1) % QN])

static int qotdfs_getattr(const char *path, struct stat *stbuf) {
    int res = 0;

    memset(stbuf, 0, sizeof(struct stat));
    if (strcmp(path, "/") == 0) {
        stbuf->st_mode = S_IFDIR | 0755;
        stbuf->st_nlink = 2;
    } else if (strcmp(path, qotdfs_path) == 0) {
        stbuf->st_mode = S_IFREG | 0444;
        stbuf->st_nlink = 1;
        stbuf->st_size = strlen(qotd);
    } else {
        res = -ENOENT;
    }

    return res;
}

static int qotdfs_readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                          off_t offset, struct fuse_file_info *fi) {
    (void) offset;
    (void) fi;

    if (strcmp(path, "/") != 0) {
        return -ENOENT;
    }

    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    filler(buf, qotdfs_path + 1, NULL, 0);

    return 0;
}

static int qotdfs_open(const char *path, struct fuse_file_info *fi) {

    if (strcmp(path, qotdfs_path) != 0)
        return -ENOENT;

    if ((fi->flags & 3) != O_RDONLY)
        return -EACCES;

    return 0;
}

static int qotdfs_read(const char *path,
                       char *buf,
                       size_t size,
                       off_t offset,
                       struct fuse_file_info *fi) {

    size_t len;
    (void) fi;
    if (strcmp(path, qotdfs_path) != 0) {
        return -ENOENT;
    }

    len = strlen(qotd);
    if (offset < len) {
        if (offset + size > len) {
            size = len - offset;
        }
        memcpy(buf, qotd + offset, size);
    } else {
        size = 0;
    }

    return size;
}

static struct fuse_operations qotdfs_oper = {
        .getattr    = qotdfs_getattr,
        .readdir    = qotdfs_readdir,
        .open        = qotdfs_open,
        .read        = qotdfs_read,
};

int main(int argc, char *argv[]) {
    time_t t = time(NULL);
    current_time = *localtime(&t);

    return fuse_main(argc, argv, &qotdfs_oper, NULL);
}
