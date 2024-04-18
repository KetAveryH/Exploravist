import { View, Text, Pressable, Image } from 'react-native'
import {TouchableOpacity, StyleSheet } from 'react-native'
import { useNavigation } from '@react-navigation/native';
import React from 'react'
import COLORS from '../const/colors';
import Button from '../components/Button';
import { LinearGradient } from "expo-linear-gradient";
import { FontAwesomeIcon } from '@fortawesome/react-native-fontawesome'
import { faCircleInfo, faLink, faGear, faLeftLong } from '@fortawesome/free-solid-svg-icons'

const Options = () => {
    const navigation = useNavigation();
    return(
        <LinearGradient
            style={{ flex: 1 }}
            colors={[COLORS.primary, COLORS.secondary]}
        >
            <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
                <Pressable onPress={() => navigation.navigate("About")}>
                    <FontAwesomeIcon icon={faCircleInfo} size={120} color="white" 
                        style={{
                            marginTop: 10, // Spacing between the two icons
                            resizeMode: "contain"
                        }}
                    />
                </Pressable>

                <Pressable onPress={() => navigation.navigate("Connect")}>
                    <FontAwesomeIcon icon={faLink} size={150} color="white"
                        style={{
                            marginTop: 70, // Spacing between the two icons
                            resizeMode: "contain"
                        }}
                    />
                </Pressable>

                <Pressable onPress={() => navigation.navigate("Settings")}>
                    <FontAwesomeIcon icon={faGear} size={120} color="white" 
                        style={{
                            marginTop: 70, // Spacing between the two icons
                            resizeMode: "contain"
                        }}
                    />
                </Pressable>
            </View>
            {/* <View style={{ flex: 1, alignItems: 'center', justifyContent: 'center' }}>
                <Pressable onPress={() => navigation.navigate("Start")}>
                    <FontAwesomeIcon icon={faLeftArrow} size={50} color="white" 
                        style={{
                            marginTop: 70, // Spacing between the two icons
                            resizeMode: "contain"
                        }}
                    />
                </Pressable>
            </View> */}
        </LinearGradient>
    )
}

export default Options