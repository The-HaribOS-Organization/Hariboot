import 'package:flutter/material.dart';


class MyHomePage extends StatefulWidget {

  const MyHomePage({super.key});

  @override
  State<MyHomePage> createState() => _MyHomePageState();
}

class _MyHomePageState extends State<MyHomePage> {

  @override
  Widget build(BuildContext context) {

    return Scaffold(
      body: Container(
        width: MediaQuery.of(context).size.width,
        height: MediaQuery.of(context).size.height,
        decoration: const BoxDecoration(
          gradient: RadialGradient(
            radius: 1.1,
            center: Alignment(-0.3, -1.0),
            colors: [
              Color(0xFF360F14),
              Color(0xFF121922),
            ],
          ),
        ),
        child: const Row(
          children: [
            NavSidebar(),
          ],
        ),
      ),
    );
  }
}

class Home extends StatefulWidget {

  const Home({super.key});

  @override
  State<Home> createState() => _HomeState();
}

class _HomeState extends State<Home> {

  @override
  Widget build(BuildContext context) {

    return 
  }
}


class NavSidebar extends StatefulWidget {

  const NavSidebar({super.key});

  @override
  State<NavSidebar> createState() => _NavSidebarState();
}

class _NavSidebarState extends State<NavSidebar> {

  @override
  Widget build(BuildContext context) {

    return Container(
      margin: EdgeInsets.all(15),
      height: MediaQuery.of(context).size.height,
      decoration: const BoxDecoration(
        color: Colors.transparent,
      ),
      child: Column(
        children: [
          const SizedBox(
            height: 5,
          ),
          Row(
            mainAxisAlignment: MainAxisAlignment.spaceAround,
            children: [
              Image.asset(
                "assets/Boot.png",
                width: 70,
                height: 70,
              ),
            ],
          ),
          const SizedBox(
            height: 125,
          ),
          const ElevatedButton(
            onPressed: null,
            style: ButtonStyle(
              backgroundColor: MaterialStatePropertyAll(Colors.transparent),
              shadowColor: MaterialStatePropertyAll(Colors.transparent),
            ),
            child: Icon(
              Icons.home,
              color: Colors.white70,
              size: 26,
            ),
          ),
          const SizedBox(
            height: 25,
          ),
          const ElevatedButton(
            onPressed: null,
            style: ButtonStyle(
              backgroundColor: MaterialStatePropertyAll(Colors.transparent),
              shadowColor: MaterialStatePropertyAll(Colors.transparent),
            ),
            child: Icon(
              Icons.new_label,
              color: Colors.white70,
              size: 26,
            ),
          ),
          const SizedBox(
            height: 25,
          ),
          const ElevatedButton(
            onPressed: null,
            style: ButtonStyle(
              backgroundColor: MaterialStatePropertyAll(Colors.transparent),
              shadowColor: MaterialStatePropertyAll(Colors.transparent),
            ),
            child: Icon(
              Icons.add,
              color: Colors.white70,
              size: 26,
            ),
          ),
          const SizedBox(
            height: 25,
          ),
          const ElevatedButton(
            onPressed: null,
            style: ButtonStyle(
              backgroundColor: MaterialStatePropertyAll(Colors.transparent),
              shadowColor: MaterialStatePropertyAll(Colors.transparent),
            ),
            child: Icon(
              Icons.contact_support,
              color: Colors.white70,
              size: 26,
            ),
          ),
          const SizedBox(
            height: 25,
          ),
          const ElevatedButton(
            onPressed: null,
            style: ButtonStyle(
              backgroundColor: MaterialStatePropertyAll(Colors.transparent),
              shadowColor: MaterialStatePropertyAll(Colors.transparent),
            ),
            child: Icon(
              Icons.web,
              color: Colors.white70,
              size: 26,
            ),
          ),
        ],
      ),
    );
  }
}