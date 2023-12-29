import 'package:flutter/material.dart';
import 'package:hariboot_mkconfig/HomePage.dart';


void main() {
  runApp(MyApp());
}

class MyApp extends StatelessWidget {

  @override
  Widget build(BuildContext context) {
    return MaterialApp(
      debugShowCheckedModeBanner: false,
      title: "Hariboot MkConfig",
      home: const MyHomePage(),
    );
  }
}
