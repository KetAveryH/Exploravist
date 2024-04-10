import { NavigationContainer } from "@react-navigation/native";
import { createNativeStackNavigator } from "@react-navigation/native-stack"
import { Start, Options } from "./screens";

const Stack = createNativeStackNavigator();

export default function App() {
  return (
    <NavigationContainer>
      <Stack.Navigator
      intitialRouteName = 'Start'
      >
      <Stack.Screen
      name = "Start"
      component = {Start}
      />

      <Stack.Screen
      name = "Options"
      component = {Options}
      />

      </Stack.Navigator>
    </NavigationContainer>
  );
}

